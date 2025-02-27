// Copyright (C) 2024 Lieuwe Huisman
#include <TApplication.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include "../Progressbar.hpp"
#include "CillindricalBoltzmannGibbs.hpp"
#include "CillindricalTsallis.hpp"
#include "EllipticalBoltzmannGibbs.hpp"
#include "FitSettings.hpp"
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

void fit(
    CFitter::MultiFitterData data,
    CFitter::MultiFitterSettings settings,
    CFitter::MultiFitterResults& results,
    const std::function<double(double*, double*)>& fitfunction,
    unsigned int fitfunction_npars) {
    size_t npar = settings.ParameterFixed.size();
    size_t npar_free = 0;
    for (int i = 0; i < npar; ++i) {
        if (!settings.ParameterFixed[i]) {
            npar_free++;
        }
    }

    CFitter::Chi2Function chi2;
    chi2.SetParindexes(settings.Indexmap);
    chi2.SetData(data.xvals, data.yvals, data.xerrs, data.yerrs);
    chi2.SetSpecies(settings.Species);
    chi2.SetFitRange(settings.FitRange);
    chi2.SetFitFunction(fitfunction, fitfunction_npars);

    size_t npoint = 0;

    for (int s = 0; s < settings.Species.size(); ++s) {
        int ts = settings.Species[s];
        for (int i = 0; i < data.xvals[ts].size(); ++i) {
            if (data.xvals[ts][i] >= settings.FitRange[ts][0] &&
                data.xvals[ts][i] <= settings.FitRange[ts][1]) {
                npoint++;
            }
        }
    }
    size_t ndf = npoint - npar_free;

    CFitter::MultiFitter fitter;
    fitter.FixPars(settings.ParameterFixed);
    fitter.LimitPars(settings.ParameterLimited);
    fitter.SetParLimits(settings.ParameterLimits);
    fitter.SetParStepsize(settings.ParameterStepsize);
    fitter.SetParNames(settings.ParameterNames);
    fitter.SetParInit(settings.ParameterInitValues);
    fitter.StepsizePars(settings.ParameterStepsized);
    fitter.PrintPars(true);

    fitter.Run(chi2);
    ROOT::Fit::FitResult finalresult = fitter.GetResult();

    double finalchi2 = chi2(fitter.GetResult().GetParams());

    finalresult.SetChi2AndNdf(finalchi2, npoint);

    results = CFitter::MultiFitterResults(settings);
    results.Chi2 = finalresult.Chi2();

    results.CorrelationMatrix.resize(npar, std::vector<double>(npar));
    results.CovarianceMatrix.resize(npar, std::vector<double>(npar));
    results.Edm = finalresult.Edm();
    results.MinFCN = finalresult.MinFcnValue();
    results.NCalls = finalresult.NCalls();
    results.DegreesOfFreedom = finalresult.Ndf();
    results.ParameterValues.resize(npar);
    results.ParameterErrors.resize(npar);
    results.settings.ParameterNames.resize(npar);
    for (index_t ipar = 0; ipar < npar; ++ipar) {
        results.ParameterValues[ipar] = finalresult.GetParams()[ipar];
        results.ParameterErrors[ipar] = finalresult.GetErrors()[ipar];
        results.settings.ParameterNames[ipar] = finalresult.GetParameterName(ipar);
    }

    for (index_t ipar = 0; ipar < npar; ++ipar) {
        for (int jpar = 0; jpar < npar; ++jpar) {
            results.CovarianceMatrix[ipar][jpar] = finalresult.CovMatrix(ipar, jpar);
            results.CorrelationMatrix[ipar][jpar] = finalresult.Correlation(ipar, jpar);
        }
    }
};

void fit_general(size_t nc,
                 CFitter::MultiFitterSettings settings,
                 const std::function<double(double*, double*)>& fitfunction,
                 unsigned int nfitfunc_npar,
                 std::string filename) {
    Datamap xdata;
    std::vector<Datamap> ydata;
    Datamap xerrs;
    std::vector<Datamap> yerrs;
    read_data(xdata, ydata, xerrs, yerrs);
    // MultifitterSettings settings(FitSets::BGBW_1);
    std::vector<CFitter::MultiFitterData> data(nc);
    std::vector<CFitter::MultiFitterResults> results(nc);

    nlohmann::json file;
    std::vector<std::string> centralitylabels = {"0-5%", "5-10%", "10-20%", "20-30%", "30-40%", "40-50%", "50-60%", "60-70%", "70-80%", "80-90%", "90-100%"};

    // Utilities::Progressbar bar(nc);
    // bar.Print();

    for (index_t ic = 0; ic < nc; ++ic) {
        data[ic] = CFitter::MultiFitterData(xdata, ydata[ic], xerrs, yerrs[ic]);

        fit(data[ic], settings, results[ic], fitfunction, nfitfunc_npar);
        results[ic].GenerateJSON();
        file["centrality"][centralitylabels[ic]] = results[ic].j;
        // bar.Update();
        // bar.Print();
    }
    // std::cout << std::endl;
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << file.dump(4);
        outFile.close();
    } else {
        throw std::runtime_error("Could not open file for writing");
    }
}

void write_curve(
    size_t nc,
    const std::function<double(double*, double*)> fitfunction,
    size_t fitfunction_npars,
    std::string file_results,
    std::string file_output) {
    const std::vector<std::string> centralitylabels = {"0-5%", "5-10%", "10-20%", "20-30%", "30-40%", "40-50%", "50-60%", "60-70%", "70-80%", "80-90%", "90-100%"};
    Datamap xdata;
    Datamap ydata;
    CFitter::MultiFitterSettings settings;
    CFitter::MultiFitterResults results;

    size_t npoints = 100;
    std::map<int, std::vector<double>> plotrange;

    std::map<int, double> plotscale =
        {
            {211, 1},
            {321, 1},
            {2212, 1}};

    std::ofstream outfile;
    outfile.open(file_output);
    nlohmann::json fitdata;

    std::ifstream infile(file_results);

    nlohmann::json jdata = nlohmann::json::parse(infile);
    infile.close();

    for (index_t ic = 0; ic < nc; ++ic) {
        Utilities::json_to_parameter(jdata["centrality"][centralitylabels[ic]], "ParameterValues", results.ParameterValues);
        Utilities::json_to_parameter(jdata["centrality"][centralitylabels[ic]]["Indexmap"], "211", settings.Indexmap[211]);
        Utilities::json_to_parameter(jdata["centrality"][centralitylabels[ic]]["Indexmap"], "321", settings.Indexmap[321]);
        Utilities::json_to_parameter(jdata["centrality"][centralitylabels[ic]]["Indexmap"], "2212", settings.Indexmap[2212]);
        Utilities::json_to_parameter(jdata["centrality"][centralitylabels[ic]], "Species", settings.Species);
        Utilities::json_to_parameter(jdata["centrality"][centralitylabels[ic]]["FitRange"], "211", plotrange[211]);
        Utilities::json_to_parameter(jdata["centrality"][centralitylabels[ic]]["FitRange"], "321", plotrange[321]);
        Utilities::json_to_parameter(jdata["centrality"][centralitylabels[ic]]["FitRange"], "2212", plotrange[2212]);
        for (int ip = 0; ip < settings.Species.size(); ++ip) {
            int pid = settings.Species[ip];
            xdata[pid].resize(npoints);
            ydata[pid].resize(npoints);
            for (int ix = 0; ix < npoints; ++ix) {
                xdata[pid][ix] = plotrange[pid][0] + ix * (plotrange[pid][1] - plotrange[pid][0]) / (npoints - 1);
                std::vector<double> vals(fitfunction_npars);
                for (int ipar = 0; ipar < fitfunction_npars; ++ipar) {
                    vals[ipar] = results.ParameterValues[settings.Indexmap[pid][ipar]];
                }
                ydata[pid][ix] = plotscale[pid] * fitfunction(&xdata[pid][ix], vals.data());
            }

            fitdata["centrality"][centralitylabels[ic]][std::to_string(pid)]["xvals"] = nlohmann::json(xdata[pid]);
            fitdata["centrality"][centralitylabels[ic]][std::to_string(pid)]["yvals"] = nlohmann::json(ydata[pid]);
        }
    }
    outfile << fitdata.dump(4);
    outfile.close();
}

void plot_bgbw(int argc, char** argv) {
    Datamap xdata;
    std::vector<Datamap> ydata;
    Datamap xerrs;
    std::vector<Datamap> yerrs;
    read_data(xdata, ydata, xerrs, yerrs);

    Datamap xdata_bgbw;
    Datamap ydata_bgbw;
    Datamap xdata_tbw;
    Datamap xdata_tbw_2;
    Datamap ydata_tbw;
    Datamap ydata_tbw_2;

    CFitter::MultiFitterSettings settings_bgbw;
    CFitter::MultiFitterResults results_bgbw;
    CFitter::MultiFitterSettings settings_tbw;
    CFitter::MultiFitterSettings settings_tbw_2;
    CFitter::MultiFitterResults results_tbw;
    CFitter::MultiFitterResults results_tbw_2;

    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-bgbw-1.json");

        nlohmann::json jdata = nlohmann::json::parse(file);

        Utilities::json_to_parameter(jdata["centrality"]["0-5%"], "ParameterValues", results_bgbw.ParameterValues);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"]["Indexmap"], "211", settings_bgbw.Indexmap[211]);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"]["Indexmap"], "321", settings_bgbw.Indexmap[321]);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"]["Indexmap"], "2212", settings_bgbw.Indexmap[2212]);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"], "Species", settings_bgbw.Species);
    }
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-tbw-1.json");

        nlohmann::json jdata = nlohmann::json::parse(file);

        Utilities::json_to_parameter(jdata["centrality"]["0-5%"], "ParameterValues", results_tbw.ParameterValues);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"]["Indexmap"], "211", settings_tbw.Indexmap[211]);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"]["Indexmap"], "321", settings_tbw.Indexmap[321]);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"]["Indexmap"], "2212", settings_tbw.Indexmap[2212]);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"], "Species", settings_tbw.Species);
    }
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-tbw-2.json");

        nlohmann::json jdata = nlohmann::json::parse(file);

        Utilities::json_to_parameter(jdata["centrality"]["0-5%"], "ParameterValues", results_tbw_2.ParameterValues);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"]["Indexmap"], "211", settings_tbw_2.Indexmap[211]);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"]["Indexmap"], "321", settings_tbw_2.Indexmap[321]);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"]["Indexmap"], "2212", settings_tbw_2.Indexmap[2212]);
        Utilities::json_to_parameter(jdata["centrality"]["0-5%"], "Species", settings_tbw_2.Species);
    }
    size_t npoints = 100;
    std::map<int, std::vector<double>> plotrange = {
        {211, {0.5, 8}},
        {321, {0.2, 8}},
        {2212, {0.3, 8}}};

    std::map<int, double> plotscale =
        {
            {211, 10E2},
            {321, 10},
            {2212, 1}};

    for (int ip = 0; ip < settings_bgbw.Species.size(); ++ip) {
        int pid = settings_bgbw.Species[ip];
        xdata_bgbw[pid].resize(npoints);
        ydata_bgbw[pid].resize(npoints);
        for (int ix = 0; ix < npoints; ++ix) {
            xdata_bgbw[pid][ix] = plotrange[pid][0] + ix * (plotrange[pid][1] - plotrange[pid][0]) / (npoints);
            double pars[5] = {
                results_bgbw.ParameterValues[settings_bgbw.Indexmap[pid][0]],
                results_bgbw.ParameterValues[settings_bgbw.Indexmap[pid][1]],
                results_bgbw.ParameterValues[settings_bgbw.Indexmap[pid][2]],
                results_bgbw.ParameterValues[settings_bgbw.Indexmap[pid][3]],
                results_bgbw.ParameterValues[settings_bgbw.Indexmap[pid][4]]};
            ydata_bgbw[pid][ix] = plotscale[pid] * BoltzmannGibbs::Cillindrical::Function(&xdata_bgbw[pid][ix], pars);
        }
    }
    for (int ip = 0; ip < settings_tbw.Species.size(); ++ip) {
        int pid = settings_tbw.Species[ip];
        xdata_tbw[pid].resize(npoints);
        ydata_tbw[pid].resize(npoints);
        for (int ix = 0; ix < npoints; ++ix) {
            xdata_tbw[pid][ix] = plotrange[pid][0] + ix * (plotrange[pid][1] - plotrange[pid][0]) / (npoints);
            double pars[7] = {
                results_tbw.ParameterValues[settings_tbw.Indexmap[pid][0]],
                results_tbw.ParameterValues[settings_tbw.Indexmap[pid][1]],
                results_tbw.ParameterValues[settings_tbw.Indexmap[pid][2]],
                results_tbw.ParameterValues[settings_tbw.Indexmap[pid][3]],
                results_tbw.ParameterValues[settings_tbw.Indexmap[pid][4]],
                results_tbw.ParameterValues[settings_tbw.Indexmap[pid][5]],
                results_tbw.ParameterValues[settings_tbw.Indexmap[pid][6]]};

            ydata_tbw[pid][ix] = plotscale[pid] * Tsallis::Cillindrical::Function(&xdata_tbw[pid][ix], pars);
        }
    }
    for (int ip = 0; ip < settings_tbw_2.Species.size(); ++ip) {
        int pid = settings_tbw_2.Species[ip];
        xdata_tbw_2[pid].resize(npoints);
        ydata_tbw_2[pid].resize(npoints);
        for (int ix = 0; ix < npoints; ++ix) {
            xdata_tbw_2[pid][ix] = plotrange[pid][0] + ix * (plotrange[pid][1] - plotrange[pid][0]) / (npoints);
            double pars[9] = {
                results_tbw_2.ParameterValues[settings_tbw_2.Indexmap[pid][0]],
                results_tbw_2.ParameterValues[settings_tbw_2.Indexmap[pid][1]],
                results_tbw_2.ParameterValues[settings_tbw_2.Indexmap[pid][2]],
                results_tbw_2.ParameterValues[settings_tbw_2.Indexmap[pid][3]],
                results_tbw_2.ParameterValues[settings_tbw_2.Indexmap[pid][4]],
                results_tbw_2.ParameterValues[settings_tbw_2.Indexmap[pid][5]],
                results_tbw_2.ParameterValues[settings_tbw_2.Indexmap[pid][6]],
                results_tbw_2.ParameterValues[settings_tbw_2.Indexmap[pid][7]],
                results_tbw_2.ParameterValues[settings_tbw_2.Indexmap[pid][8]],
            };

            ydata_tbw_2[pid][ix] = plotscale[pid] * Tsallis::Cillindrical_3::Function(&xdata_tbw_2[pid][ix], pars);
        }
    }
    TApplication app("app", &argc, argv);
    TCanvas* canvas = new TCanvas("canvas", "BGBW Plot", 800, 600);

    canvas->SetLogy();

    TGraph* Framegraph = new TGraph(1);

    std::map<int, TGraphErrors*> Datapoints;
    std::map<int, TGraph*> Fitcurve_bgbw;
    std::map<int, TGraph*> Fitcurve_tbw;
    std::map<int, TGraph*> Fitcurve_tbw_2;
    // Create TGraph objects and set their colors
    Datapoints[211] = new TGraphErrors(xdata[211].size(), xdata[211].data(), ydata[0][211].data(), xerrs[211].data(), yerrs[0][211].data());
    Datapoints[321] = new TGraphErrors(xdata[321].size(), xdata[321].data(), ydata[0][321].data(), xerrs[321].data(), yerrs[0][321].data());
    Datapoints[2212] = new TGraphErrors(xdata[2212].size(), xdata[2212].data(), ydata[0][2212].data(), xerrs[2212].data(), yerrs[0][2212].data());

    Datapoints[211]->Scale(plotscale[211]);
    Datapoints[321]->Scale(plotscale[321]);
    Datapoints[2212]->Scale(plotscale[2212]);

    Fitcurve_bgbw[211] = new TGraph(npoints, xdata_bgbw[211].data(), ydata_bgbw[211].data());
    Fitcurve_bgbw[321] = new TGraph(npoints, xdata_bgbw[321].data(), ydata_bgbw[321].data());
    Fitcurve_bgbw[2212] = new TGraph(npoints, xdata_bgbw[2212].data(), ydata_bgbw[2212].data());

    Fitcurve_tbw[211] = new TGraph(npoints, xdata_tbw[211].data(), ydata_tbw[211].data());
    Fitcurve_tbw[321] = new TGraph(npoints, xdata_tbw[321].data(), ydata_tbw[321].data());
    Fitcurve_tbw[2212] = new TGraph(npoints, xdata_tbw[2212].data(), ydata_tbw[2212].data());

    Fitcurve_tbw[211]->SetLineColor(kMagenta);
    Fitcurve_tbw[321]->SetLineColor(kMagenta);
    Fitcurve_tbw[2212]->SetLineColor(kMagenta);

    Fitcurve_tbw_2[211] = new TGraph(npoints, xdata_tbw_2[211].data(), ydata_tbw_2[211].data());
    Fitcurve_tbw_2[321] = new TGraph(npoints, xdata_tbw_2[321].data(), ydata_tbw_2[321].data());
    Fitcurve_tbw_2[2212] = new TGraph(npoints, xdata_tbw_2[2212].data(), ydata_tbw_2[2212].data());

    Fitcurve_tbw_2[211]->SetLineColor(kOrange);
    Fitcurve_tbw_2[321]->SetLineColor(kOrange);
    Fitcurve_tbw_2[2212]->SetLineColor(kOrange);

    Framegraph->GetXaxis()->SetLimits(0, 9);
    Framegraph->GetYaxis()->SetRangeUser(1E-6, 1E7);
    Framegraph->GetYaxis()->SetLabelFont(63);
    Framegraph->GetXaxis()->SetLabelFont(63);
    Framegraph->GetYaxis()->SetTitleFont(63);
    Framegraph->GetXaxis()->SetTitleFont(63);
    Framegraph->GetYaxis()->SetLabelSize(10);
    Framegraph->GetXaxis()->SetLabelSize(10);
    Framegraph->GetYaxis()->SetTitleSize(10);
    Framegraph->GetXaxis()->SetTitleSize(10);
    Datapoints[211]->SetMarkerStyle(21);
    Datapoints[321]->SetMarkerStyle(21);
    Datapoints[2212]->SetMarkerStyle(21);

    Datapoints[211]->SetLineColor(kRed);
    Datapoints[321]->SetLineColor(kBlue);
    Datapoints[2212]->SetLineColor(kGreen);
    Datapoints[211]->SetMarkerColor(kRed);
    Datapoints[321]->SetMarkerColor(kBlue);
    Datapoints[2212]->SetMarkerColor(kGreen);

    Framegraph->SetTitle("BGBW Plot;X axis title;Y axis title");
    Framegraph->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    Framegraph->GetYaxis()->SetTitle("d^{2}N/(2#pi p_{T} dp_{T} dy) (c/GeV)");

    Framegraph->Draw("AP");

    Datapoints[211]->Draw("P SAME");  // Draw the first graph with axes and lines
    Datapoints[321]->Draw("P SAME");  // Draw other graphs on the same canvas
    Datapoints[2212]->Draw("P SAME");

    Fitcurve_bgbw[211]->Draw("L SAME");  // Draw the first graph with axes and lines
    Fitcurve_bgbw[321]->Draw("L SAME");  // Draw other graphs on the same canvas
    Fitcurve_bgbw[2212]->Draw("L SAME");
    Fitcurve_tbw[211]->Draw("L SAME");  // Draw the first graph with axes and lines
    Fitcurve_tbw[321]->Draw("L SAME");  // Draw other graphs on the same canvas
    Fitcurve_tbw[2212]->Draw("L SAME");

    Fitcurve_tbw_2[211]->Draw("L SAME");  // Draw the first graph with axes and lines
    Fitcurve_tbw_2[321]->Draw("L SAME");  // Draw other graphs on the same canvas
    Fitcurve_tbw_2[2212]->Draw("L SAME");

    // Add legend
    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(Datapoints[211], "#pi^{+}+#pi^{-}", "P");
    legend->AddEntry(Datapoints[321], "K^{+}+K^{-}", "P");
    legend->AddEntry(Datapoints[2212], "p^{+}+p^{-}", "P");
    legend->SetHeader("Pb+Pb@5.02 TeV (0-5%)");
    legend->Draw("SAME");
    canvas->Modified();
    canvas->Update();

    // Run the ROOT application
    app.Run();
}

int main(int argc, char** argv) {
    std::string command;
    size_t nc = std::stoi(argv[1]);
    if (argc > 2) {
        command = argv[2];
    }
    if (command.compare("all") == 0 || command.compare("bgbw") == 0) {
        fit_general(
            nc, CFitter::FitSets::BGBW_1,
            BoltzmannGibbs::Cillindrical::Function, 5,
            "/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-bgbw-1.json");
    }
    if (command.compare("all") == 0 || command.compare("tbw") == 0) {
        fit_general(
            nc, CFitter::FitSets::TBW_1,
            Tsallis::Cillindrical::Function, 7,
            "/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-tbw-1.json");
    }
    if (command.compare("all") == 0 || command.compare("tbw_2") == 0) {
        fit_general(
            nc, CFitter::FitSets::TBW_3,
            Tsallis::Cillindrical_3::Function, 9,
            "/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-tbw-2.json");
    }
    if (command.compare("all") == 0 || command.compare("bgbw_2") == 0) {
        fit_general(
            nc, CFitter::FitSets::BGBW_2,
            BoltzmannGibbs::Elliptical_2::Function, 6,
            "/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-bgbw-2.json");
    }
    if (command.compare("plot") == 0) {
        std::cout << "Plotting results" << std::endl;
        plot_bgbw(argc, argv);
    }
    if (command.compare("write") == 0) {
        write_curve(10, BoltzmannGibbs::Cillindrical::Function, 5,
                    "/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-bgbw-1.json",
                    "/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitdata-bgbw-1.json");
        write_curve(10, Tsallis::Cillindrical::Function, 7,
                    "/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-tbw-1.json",
                    "/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitdata-tbw-1.json");
        write_curve(10, Tsallis::Cillindrical_3::Function, 9,
                    "/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-tbw-2.json",
                    "/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitdata-tbw-2.json");
    }

    // fit_tbw_all(argc, argv);

    return 0;
}