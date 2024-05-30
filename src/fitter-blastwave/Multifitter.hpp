#ifndef MULTIFITTER_HPP
#define MULTIFITTER_HPP

#include <functional>
#include <map>
#include <string>
#include <vector>

using Indexmap = std::map<int, std::vector<unsigned int>>;
using Datamap = std::map<int, std::vector<double>>;

class Chi2 {
   private:
    Indexmap parindex;
    Datamap xdata;
    Datamap ydata;
    Datamap xerrs;
    Datamap yerrs;
    Datamap fitrange;

    size_t function_npar;

    std::vector<int> species;

    size_t size_species;
    std::map<int, size_t> size_data;
    bool state_fitrange;
    std::function<double(double*, double*)> fitfunction;

    std::function<double(const double*)> operatorfunction;

    double FuncWithRange(const double* par) {
        double chi2 = 0;
        for (int ip = 0; ip < size_species; ++ip) {
            int pid = species[ip];

            size_t xsize = size_data[pid];

            for (int ix = 0; ix < xsize; ++ix) {
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
    double FuncWithoutRange(const double* par) {
        double chi2 = 0;
        for (int ip = 0; ip < size_species; ++ip) {
            int pid = species[ip];

            size_t xsize = size_data[pid];

            for (int ix = 0; ix < xsize; ++ix) {
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

   public:
    Chi2() = default;

    void SetParindexes(const Indexmap& parindex_) {
        parindex = parindex_;
    };
    void SetData(const Datamap& xdata_, const Datamap& ydata_, const Datamap& xerrs_, const Datamap& yerrs_) {
        xdata = xdata_;
        ydata = ydata_;
        xerrs = xerrs_;
        yerrs = yerrs_;
        for (auto p : xdata) {
            size_data[p.first] = xdata[p.first].size();
        }
    };
    void SetSpecies(const std::vector<int>& species_) {
        species = species_;

        size_species = species.size();
    }
    void SetFitRange(const Datamap& fitrange_) {
        fitrange = fitrange_;
        state_fitrange = true;
        // operatorfunction = &FuncWithRange;
    };

    void SetFitFunction(const std::function<double(double*, double*)>& fitfunction_, const size_t& function_npar_) {
        fitfunction = fitfunction_;
        function_npar = function_npar_;
    };

    double operator()(const double* par) {
        double chi2 = 0;
        for (int ip = 0; ip < size_species; ++ip) {
            int pid = species[ip];

            size_t xsize = size_data[pid];

            for (int ix = 0; ix < xsize; ++ix) {
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
};

class Multifitter {
   private:
    std::vector<bool> parsettings_fixed;
    std::vector<bool> parsettings_limited;
    std::vector<bool> parsettings_stepsized;
    std::vector<std::vector<double>> parsettings_limits;
    std::vector<double> parsettings_stepsize;
    std::vector<std::string> parsettings_name;
    std::vector<double> parsettings_init;
    size_t parsettings_npar;
    bool state_print;

   public:
    Multifitter() = default;
    void FixPars(const std::vector<bool>& fixed) {
        parsettings_fixed = fixed;
    };
    void LimitPars(const std::vector<bool>& limited) {
        parsettings_limited = limited;
    }
    void SetParLimits(const std::vector<std::vector<double>>& parsettings_limits_) {
        parsettings_limits = parsettings_limits_;
    };
    void SetParStepsize(const std::vector<double>& parsettings_stepsize_) {
        parsettings_stepsize = parsettings_stepsize_;
    };
    void SetParNames(const std::vector<std::string>& parsettings_name_) {
        parsettings_name = parsettings_name_;
    };
    void SetParInit(const std::vector<double>& parsettings_init_) {
        parsettings_init = parsettings_init_;
        parsettings_npar = parsettings_init.size();
    };
    void StepsizePars(const std::vector<bool>& stepsized) {
        parsettings_stepsized = stepsized;
    }
    void PrintPars(bool state_print_) {
        state_print = state_print_;
    }

    std::vector<double> Run(Chi2& chi2) {
        ROOT::Math::Functor fcn(chi2, parsettings_npar);
        ROOT::Fit::Fitter fitter;
        fitter.SetFCN(fcn, parsettings_init.data());
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
        std::vector<double> pars(parsettings_npar);
        for (int ip = 0; ip < parsettings_npar; ++ip) {
            pars[ip] = result.GetParams()[ip];
        }
        if (state_print) {
            result.Print(std::cout, true);
        }

        return pars;
    }
};

#endif