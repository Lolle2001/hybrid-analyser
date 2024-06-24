#ifndef MULTIFITTER_HPP
#define MULTIFITTER_HPP

#include <Fit/Chi2FCN.h>
#include <Fit/Fitter.h>
#include <Math/Functor.h>

#include <fstream>
#include <functional>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "fitter_utilities.hpp"

using Indexmap = std::map<int, std::vector<unsigned int>>;
using Datamap = std::map<int, std::vector<double>>;
using Datamap2D = std::map<int, std::vector<std::vector<double>>>;

namespace CFitter {
/*
[WIP]
*/
class Chi2Function {
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

    double FuncWithRange(const double* par);
    double FuncWithoutRange(const double* par);

   public:
    Chi2Function() = default;

    void SetParindexes(const Indexmap& parindex_);
    void SetData(const Datamap& xdata_, const Datamap& ydata_, const Datamap& xerrs_, const Datamap& yerrs_);
    void SetSpecies(const std::vector<int>& species_);
    void SetFitRange(const Datamap& fitrange_);
    void SetFitFunction(const std::function<double(double*, double*)>& fitfunction_, const size_t& function_npar_);

    double operator()(const double* par);
};

/*!
 * [WIP]
 */
class MultiFitter {
   private:
    std::vector<bool> parsettings_fixed;
    std::vector<bool> parsettings_limited;
    std::vector<bool> parsettings_stepsized;
    std::vector<std::vector<double>> parsettings_limits;
    std::vector<double> parsettings_stepsize;
    std::vector<std::string> parsettings_name;
    std::vector<double> parsettings_init;
    size_t parsettings_npar;
    bool state_print = false;
    ROOT::Fit::FitResult fitresult;

   public:
    MultiFitter() = default;
    void FixPars(const std::vector<bool>& fixed);
    void LimitPars(const std::vector<bool>& limited);
    void SetParLimits(const std::vector<std::vector<double>>& parsettings_limits_);
    void SetParStepsize(const std::vector<double>& parsettings_stepsize_);
    void SetParNames(const std::vector<std::string>& parsettings_name_);
    void SetParInit(const std::vector<double>& parsettings_init_);

    void StepsizePars(const std::vector<bool>& stepsized);
    void PrintPars(bool state_print_);

    void Run(Chi2Function& chi2);
    ROOT::Fit::FitResult GetResult();
};

}  // namespace CFitter

#endif