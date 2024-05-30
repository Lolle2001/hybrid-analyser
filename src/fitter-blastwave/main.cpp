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

#include "CillindricalTsallis.hpp"
#include "Multifitter.hpp"
// #include <TROOT.h>
// #include <TSystem.h>
// #include <ROOT/TProcessExecutor.hxx>
#include <omp.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include "CillindricalBoltzmannGibbs.hpp"

void test_function() {
    double A = 1.0;
    double Tkin = 0.15;
    double m0 = 0.938;
    double betas = 0.5;
    double n = 1.0;
    double params[5] = {A, Tkin, m0, betas, n};
    std::vector<double> pT;
    double ptmin = 1;
    double ptmax = 20;
    size_t npts = 100;
    for (int i = 0; i < npts; i++) {
        double pt = ptmin + (ptmax - ptmin) * i / (npts - 1);
        pT.push_back(pt);
    }
    std::ofstream file("test.dat");
    for (int i = 0; i < npts; i++) {
        double pt = pT[i];
        double result = BoltzmannGibbs::Cillindrical::Function(&pt, params);
        file << pt << " " << result << std::endl;
    }
    // double result = BoltzmannGibbs::Cillindrical::Function(&pT, params);
    // std::cout << "Result: " << result << std::endl;
}

// struct Data {
//     std::vector<double> x;
//     std::vector<double> xerr;
//     std::vector<double> y;
//     std::vector<double> yerr;
// };
void test_fit(int argc, char** argv) {
    std::map<int, std::vector<double>> xdata;
    std::map<int, std::vector<std::vector<double>>> ydata;
    std::map<int, std::vector<double>> xerrs;
    std::map<int, std::vector<std::vector<double>>> yerrs;
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chpions.json");
        nlohmann::json data = nlohmann::json::parse(file);

        ydata[211] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        yerrs[211] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[211] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[211] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chkaons.json");
        nlohmann::json data = nlohmann::json::parse(file);

        ydata[321] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        yerrs[321] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[321] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[321] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chprotons.json");
        nlohmann::json data = nlohmann::json::parse(file);

        ydata[2212] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        yerrs[2212] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[2212] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[2212] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }

    std::vector<double> fxdata;
    std::vector<double> fydata;
    double A = 1.0;
    double Tkin = 0.15;
    double m0 = 0.938;
    double betas = 0.5;
    double n = 1.0;
    double params[5] = {A, Tkin, m0, betas, n};

    double ptmin = 1;
    double ptmax = 20;
    size_t npts = 100;
    for (int i = 0; i < npts; i++) {
        double pt = ptmin + (ptmax - ptmin) * i / (npts - 1);
        fxdata.push_back(pt);
    }

    for (int i = 0; i < npts; i++) {
        double pt = fxdata[i];
        double result = BoltzmannGibbs::Cillindrical::Function(&pt, params);
        fydata.push_back(result);
    }

    TF1* fitfunc = new TF1("f1", BoltzmannGibbs::Cillindrical::Function, 0.1, 3, 5);
    fitfunc->SetParameters(params);
    fitfunc->SetParLimits(0, 0.01, 100000);
    fitfunc->SetParLimits(1, 0.05, 0.25);
    fitfunc->FixParameter(2, 0.138);
    fitfunc->SetParLimits(3, 0.01, 1);
    fitfunc->SetParLimits(4, 0.01, 2);

    TApplication app("app", &argc, argv);

    TCanvas* canvas = new TCanvas();

    canvas->SetLogx();
    canvas->SetLogy();
    TGraph* Frame = new TGraph(1);
    TGraphErrors* hist211 = new TGraphErrors(xdata[211].size(), &xdata[211][0], &ydata[211][0][0], &xerrs[211][0], &yerrs[211][0][0]);
    TGraphErrors* hist321 = new TGraphErrors(xdata[321].size(), &xdata[321][0], &ydata[321][0][0], &xerrs[321][0], &yerrs[321][0][0]);
    TGraphErrors* hist2212 = new TGraphErrors(xdata[2212].size(), &xdata[2212][0], &ydata[2212][0][0], &xerrs[2212][0], &yerrs[2212][0][0]);

    TGraph* fhist = new TGraph(fxdata.size(), &fxdata[0], &fydata[0]);

    Frame->GetXaxis()->SetLimits(0, 20);
    Frame->GetYaxis()->SetRangeUser(1E-8, 1E4);
    Frame->Draw("AP");

    hist211->Draw("SAME");
    hist211->SetLineColor(kBlue);
    hist211->SetMarkerColor(kBlue);
    hist321->Draw("SAME");
    hist321->SetLineColor(kRed);
    hist321->SetMarkerColor(kRed);
    hist2212->Draw("SAME");
    hist2212->SetLineColor(kGreen);
    hist2212->SetMarkerColor(kGreen);
    fitfunc->Draw("SAME");

    // fhist->Draw("SAME");
    canvas->Modified();
    canvas->Update();

    app.Run();
}

void test_multifit(int argc, char** argv) {
    std::map<int, std::vector<double>> xdata;
    std::map<int, std::vector<std::vector<double>>> ydata;
    std::map<int, std::vector<double>> xerrs;
    std::map<int, std::vector<std::vector<double>>> yerrs;
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chpions.json");
        nlohmann::json data = nlohmann::json::parse(file);

        ydata[211] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        yerrs[211] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[211] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[211] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chkaons.json");
        nlohmann::json data = nlohmann::json::parse(file);

        ydata[321] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        yerrs[321] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[321] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[321] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chprotons.json");
        nlohmann::json data = nlohmann::json::parse(file);

        ydata[2212] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        yerrs[2212] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[2212] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[2212] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    std::vector<std::vector<int>> parindexes =
        {{0, 3, 4, 7, 8},
         {1, 3, 5, 7, 8},
         {2, 3, 6, 7, 8}};

    std::vector<int> pids = {211, 321, 2212};
    double mass[3] = {0.140, 0.498, 0.938};
    auto chi2Function = [&](const Double_t* par) {
        // minimisation function computing the sum of squares of residuals
        double chi2 = 0;
        for (int ip = 0; ip < pids.size(); ++ip) {
            for (int ix = 0; ix < xdata[pids[ip]].size(); ++ix) {
                double xerr = xerrs[pids[ip]][ix];
                double x = xdata[pids[ip]][ix];
                double y = ydata[pids[ip]][0][ix];
                double yerr = yerrs[pids[ip]][0][ix];

                // cout << "i_point = " << i_point << ", pt_data = " << pt_data << "v2 = " << v2_data << " +/- " << v2_err << endl;

                if (x < 2.5) {
                    double v2_BW = 0;
                    double inv_yield_BW = 0;

                    // blast wave parameters
                    // in GeV
                    const double m = par[parindexes[ip][2]];  // in GeV
                    const double T = par[parindexes[ip][1]];  // fit parameter: Temp in GeV
                    const double A = par[parindexes[ip][0]];
                    const double beta = par[parindexes[ip][3]];
                    const double n = par[parindexes[ip][4]];
                    double pars[5] = {A, T, m, beta, n};
                    double res = BoltzmannGibbs::Cillindrical::Function(&x, pars);

                    // cout << "i_point = " << i_point << ", pt_BW = " << pt_BW << ", v2_BW = " << v2_BW << endl;
                    double diff = (res - y) / yerr;
                    chi2 += diff * diff;
                }
            }
        }
        return chi2;
    };
    std::vector<double> parinit = {1, 1, 1, 0.11, 0.138, 0.498, 0.938, 0.5, 1.0};

    ROOT::Math::Functor fcn(chi2Function, 9);
    ROOT::Fit::Fitter fitter;
    // ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(1);

    double* pStart = &parinit[0];
    fitter.SetFCN(fcn, pStart);

    fitter.Config().ParSettings(0).SetName("A211");   // set parameters name
    fitter.Config().ParSettings(1).SetName("A321");   // set parameters name
    fitter.Config().ParSettings(2).SetName("A2212");  // set parameters name
    fitter.Config().ParSettings(3).SetName("Tkin");   // set parameters name
    fitter.Config().ParSettings(4).SetName("M211");   // set parameters name
    fitter.Config().ParSettings(5).SetName("M321");   // set parameters name
    fitter.Config().ParSettings(6).SetName("M2212");  // set parameters name
    fitter.Config().ParSettings(7).SetName("BetaS");  // set parameters name
    fitter.Config().ParSettings(8).SetName("N");      // set parameters name

    // fitter.Config().ParSettings(0).SetLimits(0.01,0.30); // set parameters range

    fitter.Config().ParSettings(0).SetLimits(1, 1000000);
    fitter.Config().ParSettings(1).SetLimits(1, 1000000);
    fitter.Config().ParSettings(2).SetLimits(1, 1000000);
    fitter.Config().ParSettings(3).SetLimits(0.01, 0.3);
    fitter.Config().ParSettings(4).Fix();
    fitter.Config().ParSettings(5).Fix();
    fitter.Config().ParSettings(6).Fix();
    fitter.Config().ParSettings(7).SetLimits(0.01, 1);
    fitter.Config().ParSettings(8).SetLimits(0.01, 2);
    // fitter.Config().ParSettings(8).Fix();

    fitter.Config().ParSettings(0).SetStepSize(1);  // set parameters minimizer step size
    fitter.Config().ParSettings(1).SetStepSize(1);
    fitter.Config().ParSettings(2).SetStepSize(1);
    fitter.Config().ParSettings(3).SetStepSize(0.01);
    fitter.Config().ParSettings(4).SetStepSize(0.01);  // set parameters minimizer step size
    fitter.Config().ParSettings(5).SetStepSize(0.01);
    fitter.Config().ParSettings(6).SetStepSize(0.01);
    fitter.Config().ParSettings(7).SetStepSize(0.01);
    fitter.Config().ParSettings(8).SetStepSize(0.01);

    // fitter.Config().SetMinimizer("Minuit", "Migrad");  // set minimizer
    fitter.Config().SetMinimizer("Minuit2", "Migrad");  // set minimizer

    // do the fit
    bool ok = fitter.FitFCN();
    if (!ok) {
        Error("BWFit", "BlastWave Fit failed");
    }

    const ROOT::Fit::FitResult& result = fitter.Result();
    result.Print(std::cout);

    const double* fitpars = result.GetParams();

    TF1* f211 = new TF1("f211", BoltzmannGibbs::Cillindrical::Function, 0.1, 20, 5);
    TF1* f321 = new TF1("f321", BoltzmannGibbs::Cillindrical::Function, 0.2, 20, 5);
    TF1* f2212 = new TF1("f2212", BoltzmannGibbs::Cillindrical::Function, 0.3, 20, 5);
    f211->SetParameter(0, fitpars[0]);
    f211->SetParameter(1, fitpars[3]);
    f211->SetParameter(2, fitpars[4]);
    f211->SetParameter(3, fitpars[7]);
    f211->SetParameter(4, fitpars[8]);
    f321->SetParameter(0, fitpars[1]);
    f321->SetParameter(1, fitpars[3]);
    f321->SetParameter(2, fitpars[5]);
    f321->SetParameter(3, fitpars[7]);
    f321->SetParameter(4, fitpars[8]);
    f2212->SetParameter(0, fitpars[2]);
    f2212->SetParameter(1, fitpars[3]);
    f2212->SetParameter(2, fitpars[6]);
    f2212->SetParameter(3, fitpars[7]);
    f2212->SetParameter(4, fitpars[8]);

    double scaleFactor211 = 10.0;
    double scaleFactor321 = 5.0;
    double scaleFactor2212 = 1.0;

    TF1* f211_scaled = new TF1("f211_scaled", [f211, scaleFactor211](double* x, double* params) { return scaleFactor211 * f211->Eval(x[0]); }, 0.1, 20, 0);

    TF1* f321_scaled = new TF1("f321_scaled", [f321, scaleFactor321](double* x, double* params) { return scaleFactor321 * f321->Eval(x[0]); }, 0.2, 20, 0);

    TF1* f2212_scaled = new TF1("f2212_scaled", [f2212, scaleFactor2212](double* x, double* params) { return scaleFactor2212 * f2212->Eval(x[0]); }, 0.3, 20, 0);

    TApplication app("app", &argc, argv);

    TCanvas* canvas = new TCanvas();

    canvas->SetLogx();
    canvas->SetLogy();
    TGraph* Frame = new TGraph(1);
    TGraphErrors* hist211 = new TGraphErrors(xdata[211].size(), &xdata[211][0], &ydata[211][0][0], &xerrs[211][0], &yerrs[211][0][0]);
    TGraphErrors* hist321 = new TGraphErrors(xdata[321].size(), &xdata[321][0], &ydata[321][0][0], &xerrs[321][0], &yerrs[321][0][0]);
    TGraphErrors* hist2212 = new TGraphErrors(xdata[2212].size(), &xdata[2212][0], &ydata[2212][0][0], &xerrs[2212][0], &yerrs[2212][0][0]);

    hist211->Scale(10);
    hist321->Scale(5);
    hist2212->Scale(1);
    // TGraph* fplot211 = new TGraph(f211);
    // fplot211->GetXaxis()->SetLimits(0.1, 3);

    // fplot211->Scale(10);
    // TGraph* fplot321 = new TGraph(f321);
    // fplot321->GetXaxis()->SetLimits(0.2, 3);
    // fplot321->Scale(5);
    // TGraph* fplot2212 = new TGraph(f2212);
    // fplot2212->GetXaxis()->SetLimits(0.3, 3);
    // fplot2212->Scale(1);

    Frame->GetXaxis()->SetLimits(0.1, 3);
    Frame->GetYaxis()->SetRangeUser(1E-2, 1E6);
    Frame->Draw("AP");

    hist211->Draw("SAME");
    hist211->SetLineColor(kBlue);
    hist211->SetMarkerColor(kBlue);
    hist321->Draw("SAME");
    hist321->SetLineColor(kRed);
    hist321->SetMarkerColor(kRed);
    hist2212->Draw("SAME");
    hist2212->SetLineColor(kGreen);
    hist2212->SetMarkerColor(kGreen);
    f211_scaled->Draw("L SAME");
    f321_scaled->Draw("L SAME");
    f2212_scaled->Draw("L SAME");

    // fhist->Draw("SAME");
    canvas->Modified();
    canvas->Update();

    app.Run();
}

struct RGB {
   public:
    float r;
    float g;
    float b;
    RGB(){};
    RGB(float r_, float g_, float b_) : r(r_), g(g_), b(b_){};
};

void test_multifit_all(int argc, char** argv) {
    std::map<int, std::vector<double>> xdata;
    std::map<int, std::vector<std::vector<double>>> ydata;
    std::map<int, std::vector<double>> xerrs;
    std::map<int, std::vector<std::vector<double>>> yerrs;
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chpions.json");
        nlohmann::json data = nlohmann::json::parse(file);

        ydata[211] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        yerrs[211] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[211] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[211] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chkaons.json");
        nlohmann::json data = nlohmann::json::parse(file);

        ydata[321] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        yerrs[321] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[321] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[321] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chprotons.json");
        nlohmann::json data = nlohmann::json::parse(file);

        ydata[2212] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        yerrs[2212] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[2212] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[2212] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    std::vector<std::vector<int>> parindexes =
        {{0, 3, 4, 7, 8},
         {1, 3, 5, 7, 8},
         {2, 3, 6, 7, 8}};

    std::vector<int> pids = {211, 321, 2212};
    double mass[3] = {0.140, 0.498, 0.938};

    std::map<int, std::vector<double>> fitrange =
        {
            {211, {0.5, 1}},
            {321, {0.2, 1.5}},
            {2212, {0.3, 3.0}}};

    size_t nc = 9;  // ydata[211].size();
    // std::cout << ydata[211].size() << std::endl;
    std::vector<bool> errorstate(nc);
    std::vector<std::vector<double>> finalparams(nc);
    // #pragma omp parallel for shared(pids, mass, xdata, ydata, xerrs, yerrs, parindexes)
    for (int ic = 0; ic < nc; ++ic) {
        auto chi2Function = [&](const Double_t* par) {
            // minimisation function computing the sum of squares of residuals
            double chi2 = 0;
            for (int ip = 0; ip < pids.size(); ++ip) {
                int pid = pids[ip];
                for (int ix = 0; ix < xdata[pids[ip]].size(); ++ix) {
                    double xerr = xerrs[pids[ip]][ix];
                    double x = xdata[pids[ip]][ix];
                    double y = ydata[pids[ip]][ic][ix];
                    double yerr = yerrs[pids[ip]][ic][ix];

                    // cout << "i_point = " << i_point << ", pt_data = " << pt_data << "v2 = " << v2_data << " +/- " << v2_err << endl;

                    if (x >= fitrange[pid][0] && x <= fitrange[pid][1]) {
                        double v2_BW = 0;
                        double inv_yield_BW = 0;

                        // blast wave parameters
                        // in GeV
                        const double m = par[parindexes[ip][2]];  // in GeV
                        const double T = par[parindexes[ip][1]];  // fit parameter: Temp in GeV
                        const double A = par[parindexes[ip][0]];
                        const double beta = par[parindexes[ip][3]];
                        const double n = par[parindexes[ip][4]];
                        double pars[5] = {A, T, m, beta, n};
                        double res = BoltzmannGibbs::Cillindrical::Function(&x, pars);

                        // cout << "i_point = " << i_point << ", pt_BW = " << pt_BW << ", v2_BW = " << v2_BW << endl;
                        double diff = (res - y) / yerr;
                        chi2 += diff * diff;
                    }
                }
            }
            return chi2;
        };
        std::vector<double> parinit = {1, 1, 1, 0.11, 0.138, 0.498, 0.938, 0.5, 1.0};

        ROOT::Math::Functor fcn(chi2Function, 9);
        ROOT::Fit::Fitter fitter;
        // ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(1);

        double* pStart = &parinit[0];
        fitter.SetFCN(fcn, pStart);

        fitter.Config().ParSettings(0).SetName("A211");   // set parameters name
        fitter.Config().ParSettings(1).SetName("A321");   // set parameters name
        fitter.Config().ParSettings(2).SetName("A2212");  // set parameters name
        fitter.Config().ParSettings(3).SetName("Tkin");   // set parameters name
        fitter.Config().ParSettings(4).SetName("M211");   // set parameters name
        fitter.Config().ParSettings(5).SetName("M321");   // set parameters name
        fitter.Config().ParSettings(6).SetName("M2212");  // set parameters name
        fitter.Config().ParSettings(7).SetName("BetaS");  // set parameters name
        fitter.Config().ParSettings(8).SetName("N");      // set parameters name

        // fitter.Config().ParSettings(0).SetLimits(0.01,0.30); // set parameters range

        fitter.Config().ParSettings(0).SetLimits(1, 10000000);
        fitter.Config().ParSettings(1).SetLimits(1, 10000000);
        fitter.Config().ParSettings(2).SetLimits(1, 10000000);
        fitter.Config().ParSettings(3).SetLimits(0.01, 0.3);
        fitter.Config().ParSettings(4).Fix();
        fitter.Config().ParSettings(5).Fix();
        fitter.Config().ParSettings(6).Fix();
        fitter.Config().ParSettings(7).SetLimits(0.01, 1);
        fitter.Config().ParSettings(8).SetLimits(0.01, 3);
        // fitter.Config().ParSettings(8).Fix();

        fitter.Config().ParSettings(0).SetStepSize(1);  // set parameters minimizer step size
        fitter.Config().ParSettings(1).SetStepSize(1);
        fitter.Config().ParSettings(2).SetStepSize(1);
        fitter.Config().ParSettings(3).SetStepSize(0.01);
        fitter.Config().ParSettings(4).SetStepSize(0.01);  // set parameters minimizer step size
        fitter.Config().ParSettings(5).SetStepSize(0.01);
        fitter.Config().ParSettings(6).SetStepSize(0.01);
        fitter.Config().ParSettings(7).SetStepSize(0.01);
        fitter.Config().ParSettings(8).SetStepSize(0.01);

        fitter.Config().SetMinimizer("Minuit", "Migrad");  // set minimizer
        // fitter.Config().SetMinimizer("Minuit2", "Migrad");  // set minimizer

        // do the fit
        bool ok = fitter.FitFCN();
        if (!ok) {
            Error("BWFit", "BlastWave Fit failed");
            errorstate[ic] = true;
            break;
        } else {
            const ROOT::Fit::FitResult& result = fitter.Result();
            result.Print(std::cout, true);
            std::vector<double> fpars(9);
            for (int i = 0; i < 9; ++i) {
                fpars[i] = result.GetParams()[i];
            }
            finalparams[ic] = fpars;
        }
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
            if (!errorstate[ic]) {
                fitfunctions[ic][pid] = std::make_shared<TF1>("", BoltzmannGibbs::Cillindrical::Function, ranges[pid][0], ranges[pid][1], 5);
                for (int p = 0; p < 5; ++p) {
                    // std::cout << finalparams[ic][parindexes[ip][p]] << std::endl;
                    fitfunctions[ic][pid]->SetParameter(p, finalparams[ic][parindexes[ip][p]]);
                }
                fitfunctions_scaled[ic][pid] = std::make_shared<TF1>("", [fitfunctions, ic, pid, scalefactor](double* x, double* params) { return scalefactor.at(ic) * fitfunctions[ic].at(pid)->Eval(x[0]); }, ranges[pid][0], ranges[pid][1], 0);
            }
            hists[ic][pid] = std::make_shared<TGraphErrors>(xdata[pid].size(), &xdata[pid][0], &ydata[pid][ic][0], &xerrs[pid][0], &yerrs[pid][ic][0]);
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
        if (!errorstate[ic]) {
            fitfunctions_scaled[ic][pid]->Draw("L SAME");
            //     // fitfunctions[ic][pid]->Draw("L SAME");
            fitfunctions_scaled[ic][pid]->SetLineColor(kBlack);
        }
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

void test_tsallis() {
    double A = 1.0;
    double Tkin = 0.15;
    double m0 = 0.938;
    double betas = 0.5;
    double n = 1.0;
    double q = 1.1;
    double yb = 0.5;

    double params[7] = {A, Tkin, m0, betas, n, q, yb};
    std::vector<double> pT;
    double ptmin = 1;
    double ptmax = 20;
    size_t npts = 100;
    for (int i = 0; i < npts; i++) {
        double pt = ptmin + (ptmax - ptmin) * i / (npts - 1);
        pT.push_back(pt);
    }
    std::ofstream file("test.dat");
    for (int i = 0; i < npts; i++) {
        double pt = pT[i];
        double result = Tsallis::Cillindrical::Function(&pt, params);
        file << pt << " " << result << std::endl;
    }
    // double result = BoltzmannGibbs::Cillindrical::Function(&pT, params);
    // std::cout << "Result: " << result << std::endl;
}

double exampleFitFunction(double* x, double* par) {
    double A = par[0];
    double B = par[1];
    // Example function: A * exp(-B * x)
    return A * std::exp(-B * x[0]);
}

int test_multifitter(int arg, char** argv) {
    Chi2 chi2;

    // Set up parameters, data, etc.
    Indexmap parindex = {{1, {0, 1}}, {2, {0, 1}}};  // Example index mapping
    Datamap xdata = {{1, {1.0, 2.0, 3.0}}, {2, {1.0, 2.0, 3.0}}};
    Datamap ydata = {{1, {2.0, 1.5, 1.2}}, {2, {1.0, 2.0, 3.0}}};
    Datamap xerrs = {{1, {0.1, 0.1, 0.1}}, {2, {1.0, 2.0, 3.0}}};
    Datamap yerrs = {{1, {0.2, 0.2, 0.2}}, {2, {1.0, 2.0, 3.0}}};
    Datamap fitrange = {{1, {0.0, 3.0}}, {2, {0.0, 3.0}}};
    std::vector<int> species = {1, 2};
    std::vector<double> initial_params = {1.0, 0.1};

    chi2.SetParindexes(parindex);
    chi2.SetSpecies(species);
    chi2.SetData(xdata, ydata, xerrs, yerrs);
    chi2.SetFitRange(fitrange);
    chi2.SetFitFunction(exampleFitFunction, 2);

    // Example parameters to evaluate chi2
    double params[] = {1.0, 0.1};
    double chi2_value = chi2(params);

    std::cout << "Chi2 value: " << chi2_value << std::endl;

    return 0;
}

double LinearFitFunction(double* x, double* params) {
    double m = params[0];
    double b = params[1];
    return m * (*x) + b;
}

void TestMultifitter() {
    // Create mock data for two species
    Indexmap parindex = {
        {0, {0, 1}},
        {1, {2, 3}}};

    Datamap xdata = {
        {0, {1.0, 2.0, 3.0}},
        {1, {1.0, 2.0, 3.0}}};
    Datamap ydata = {
        {0, {2.0, 4.0, 6.0}},
        {1, {3.0, 6.0, 9.0}}};
    Datamap xerrs = {
        {0, {0.1, 0.1, 0.1}},
        {1, {0.1, 0.1, 0.1}}};
    Datamap yerrs = {
        {0, {0.1, 0.1, 0.1}},
        {1, {0.1, 0.1, 0.1}}};
    Datamap fitrange = {
        {0, {1.0, 3.0}},
        {1, {1.0, 3.0}}};

    Chi2 chi2;
    chi2.SetParindexes(parindex);
    chi2.SetData(xdata, ydata, xerrs, yerrs);
    chi2.SetSpecies({0, 1});
    chi2.SetFitRange(fitrange);
    chi2.SetFitFunction(LinearFitFunction, 2);

    Multifitter fitter;
    fitter.FixPars({false, false, false, false});
    fitter.LimitPars({false, false, false, false});
    fitter.SetParStepsize({0.01, 0.01, 0.01, 0.01});
    fitter.SetParNames({"m1", "b1", "m2", "b2"});
    fitter.SetParInit({1.0, 0.0, 1.0, 1.0});
    fitter.StepsizePars({true, true, true, true});
    fitter.PrintPars(true);

    std::vector<double> results = fitter.Run(chi2);

    std::cout << "Fitted parameters:" << std::endl;
    for (size_t i = 0; i < 4; ++i) {
        std::cout << "Parameter " << i << ": " << results[i] << std::endl;
    }

    // Plot the results
    TCanvas* canvas = new TCanvas("canvas", "Fit Results", 800, 600);

    int npoints = xdata[0].size() + xdata[1].size();
    TGraphErrors* graph = new TGraphErrors(npoints);

    int point = 0;
    for (int i = 0; i < xdata[0].size(); ++i) {
        graph->SetPoint(point, xdata[0][i], ydata[0][i]);
        graph->SetPointError(point, xerrs[0][i], yerrs[0][i]);
        ++point;
    }
    for (int i = 0; i < xdata[1].size(); ++i) {
        graph->SetPoint(point, xdata[1][i], ydata[1][i]);
        graph->SetPointError(point, xerrs[1][i], yerrs[1][i]);
        ++point;
    }

    graph->SetTitle("Fit Results;X;Y");
    graph->SetMarkerStyle(21);
    graph->Draw("AP");
    graph->GetXaxis()->SetLimits(0, 4);
    graph->GetYaxis()->SetRangeUser(0, 10);

    TF1* fitFunc1 = new TF1("fitFunc1", "[0]*x + [1]", 0, 4.0);
    fitFunc1->SetParameters(results[0], results[1]);
    fitFunc1->SetLineColor(kRed);
    fitFunc1->Draw("same");

    TF1* fitFunc2 = new TF1("fitFunc2", "[0]*x + [1]", 0, 4.0);
    fitFunc2->SetParameters(results[2], results[3]);
    fitFunc2->SetLineColor(kBlue);
    fitFunc2->Draw("same");

    canvas->SaveAs("fit_results.png");

    delete canvas;
    delete graph;
    delete fitFunc1;
    delete fitFunc2;
}

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

void MultifitAll(int argc, char** argv) {
    Datamap xdata;
    std::vector<Datamap> ydata;
    Datamap xerrs;
    std::vector<Datamap> yerrs;
    read_data(xdata, ydata, xerrs, yerrs);
    std::cout << "after" << std::endl;
    Indexmap parindexes =
        {{211, {0, 3, 4, 7, 8}},
         {321, {1, 3, 5, 7, 8}},
         {2212, {2, 3, 6, 7, 8}}};

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
        std::cout << ic << std::endl;
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

        finalparams[ic] = fitter.Run(chi2);
        std::cout << ic << std::endl;
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
    std::cout << "after" << std::endl;
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
        std::cout << ic << std::endl;

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

        finalparams[ic] = fitter.Run(chi2);
        std::cout << ic << std::endl;
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

int main(int argc, char* argv[]) {
    // test_multifit_all(argc, argv);
    // test_tsallis();
    // test_multifitter(argc, argv);
    // TestMultifitter();
    MultifitAll(argc, argv);
    // MultifitTsallis(argc, argv);
    return 0;
}