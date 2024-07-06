// Copyright (C) 2024 Lieuwe Huisman
#include "Multifitter.hpp"
namespace CFitter {
double Chi2Function::FuncWithRange(const double* par) {
    double chi2 = 0;
    for (int ip = 0; ip < size_species; ++ip) {
        int pid = species[ip];

        size_t xsize = size_data[pid];

        for (index_t ix = 0; ix < xsize; ++ix) {
            // double xerr = xerrs[pid][ix];
            double x = xdata[pid][ix];
            double yerr = yerrs[pid][ix];
            double y = ydata[pid][ix];

            if (x >= fitrange[pid][0] && x <= fitrange[pid][1]) {
                std::vector<double> vals(function_npar);
                for (int ipar = 0; ipar < function_npar; ++ipar) {
                    vals[ipar] = par[parindex[pid][ipar]];
                }

                double res = fitfunction(&x, vals.data());
                // std::cout << ip << " " << ix << " " << std::endl;
                // double res = 0;
                double diff = (res - y) / yerr;
                chi2 += diff * diff;
            }
        }
    }
    return chi2;
};
double Chi2Function::FuncWithoutRange(const double* par) {
    double chi2 = 0;
    for (int ip = 0; ip < size_species; ++ip) {
        int pid = species[ip];

        size_t xsize = size_data[pid];

        for (index_t ix = 0; ix < xsize; ++ix) {
            // double xerr = xerrs[pid][ix];
            double x = xdata[pid][ix];
            double yerr = yerrs[pid][ix];
            double y = ydata[pid][ix];

            std::vector<double> vals(function_npar);
            for (int ipar = 0; ipar < function_npar; ++ipar) {
                vals[ipar] = par[parindex[pid][ipar]];
            }

            double res = fitfunction(&x, vals.data());
            // std::cout << ip << " " << ix << " " << std::endl;
            // double res = 0;
            double diff = (res - y) / yerr;
            chi2 += diff * diff;
        }
    }
    return chi2;
};

void Chi2Function::SetParindexes(const Indexmap& parindex_) {
    parindex = parindex_;
};
void Chi2Function::SetData(const Datamap& xdata_, const Datamap& ydata_, const Datamap& xerrs_, const Datamap& yerrs_) {
    xdata = xdata_;
    ydata = ydata_;
    xerrs = xerrs_;
    yerrs = yerrs_;
    for (auto p : xdata) {
        size_data[p.first] = xdata[p.first].size();
    }
};
void Chi2Function::SetSpecies(const std::vector<int>& species_) {
    species = species_;

    size_species = species.size();
}
void Chi2Function::SetFitRange(const Datamap& fitrange_) {
    fitrange = fitrange_;
    state_fitrange = true;
    // operatorfunction = &FuncWithRange;
};

void Chi2Function::SetFitFunction(const std::function<double(double*, double*)>& fitfunction_, const size_t& function_npar_) {
    fitfunction = fitfunction_;
    function_npar = function_npar_;
};

double Chi2Function::operator()(const double* par) {
    double chi2 = 0;
    for (int ip = 0; ip < size_species; ++ip) {
        int pid = species[ip];

        size_t xsize = size_data[pid];

        for (index_t ix = 0; ix < xsize; ++ix) {
            // double xerr = xerrs[pid][ix];
            double x = xdata[pid][ix];
            double yerr = yerrs[pid][ix];
            double y = ydata[pid][ix];

            if (x >= fitrange[pid][0] && x <= fitrange[pid][1]) {
                std::vector<double> vals(function_npar);
                for (int ipar = 0; ipar < function_npar; ++ipar) {
                    vals[ipar] = par[parindex[pid][ipar]];
                }

                double res = fitfunction(&x, vals.data());
                // std::cout << ip << " " << ix << " " << std::endl;
                // double res = 0;
                double diff = (res - y) / yerr;
                chi2 += diff * diff;
            }
        }
    }
    return chi2;
};

void MultiFitter::FixPars(const std::vector<bool>& fixed) {
    parsettings_fixed = fixed;
};
void MultiFitter::LimitPars(const std::vector<bool>& limited) {
    parsettings_limited = limited;
}
void MultiFitter::SetParLimits(const std::vector<std::vector<double>>& parsettings_limits_) {
    parsettings_limits = parsettings_limits_;
};
void MultiFitter::SetParStepsize(const std::vector<double>& parsettings_stepsize_) {
    parsettings_stepsize = parsettings_stepsize_;
};
void MultiFitter::SetParNames(const std::vector<std::string>& parsettings_name_) {
    parsettings_name = parsettings_name_;
};
void MultiFitter::SetParInit(const std::vector<double>& parsettings_init_) {
    parsettings_init = parsettings_init_;
    parsettings_npar = parsettings_init.size();
};
void MultiFitter::StepsizePars(const std::vector<bool>& stepsized) {
    parsettings_stepsized = stepsized;
}
void MultiFitter::PrintPars(bool state_print_) {
    state_print = state_print_;
}

void MultiFitter::Run(Chi2Function& chi2) {
    ROOT::Math::Functor fcn(chi2, parsettings_npar);
    ROOT::Fit::Fitter fitter;
    fitter.SetFCN(fcn, parsettings_init.data());
    // fitter.SetData(ROOT::Fit::BinData());

    for (int ipar = 0; ipar < parsettings_npar; ++ipar) {
        fitter.Config().ParSettings(ipar).SetName(parsettings_name[ipar]);
        if (parsettings_limited[ipar]) {
            fitter.Config().ParSettings(ipar).SetLimits(parsettings_limits[ipar][0], parsettings_limits[ipar][1]);
        }
        if (parsettings_fixed[ipar]) {
            fitter.Config().ParSettings(ipar).Fix();
        }
        if (parsettings_stepsized[ipar]) {
            fitter.Config().ParSettings(ipar).SetStepSize(parsettings_stepsize[ipar]);
        }
    }
    fitter.Config().SetMinimizer("Minuit", "Migrad");
    bool ok = fitter.FitFCN();
    if (!ok) {
        Error("BWFit", "BlastWave Fit failed");
        // errorstate[ic] = true;
    }
    const ROOT::Fit::FitResult& result = fitter.Result();
    fitresult = ROOT::Fit::FitResult(result);

    if (state_print) {
        result.Print(std::cout, true);
        std::cout << std::endl;
    }
}

ROOT::Fit::FitResult MultiFitter::GetResult() {
    return fitresult;
}

}