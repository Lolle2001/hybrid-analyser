#ifndef CILLINDRICALBOLTZMANNGIBBS_HPP
#define CILLINDRICALBOLTZMANNGIBBS_HPP

#include <TMath.h>

#include <boost/math/quadrature/gauss_kronrod.hpp>
#include <boost/math/special_functions/bessel.hpp>

#include "Data.hpp"

namespace BoltzmannGibbs {
namespace Cillindrical {
double Integrand(double* x, double* par) {
    double xi = x[0];
    double mT = par[0];
    double pT = par[1];
    double betas = par[2];
    double Tkin = par[3];
    double n = par[4];

    // double arg0 = betas * std::pow(xi, n);
    // double rho = std::atanh(arg0);
    // double arg1 = mT * std::cosh(rho) / Tkin;
    // double arg2 = pT * std::sinh(rho) / Tkin;
    // double k1 = boost::math::cyl_bessel_k(1, arg1);
    // double i0 = boost::math::cyl_bessel_i(0, arg2);

    double arg0 = betas * TMath::Power(xi, n);
    double rho = TMath::ATanH(arg0);
    double arg1 = mT * TMath::CosH(rho) / Tkin;
    double arg2 = pT * TMath::SinH(rho) / Tkin;
    double k1 = TMath::BesselK1(arg1);
    double i0 = TMath::BesselI0(arg2);

    return xi * k1 * i0;
}

double Function(double* x, double* par) {
    double pT = x[0];
    double A = par[0];
    double Tkin = par[1];
    double m0 = par[2];
    double betas = par[3];
    double n = par[4];
    double mT = std::sqrt(m0 * m0 + pT * pT);

    double xmin = 0.0;
    double xmax = 1.0;

    // Integrand parameters
    double integrandParams[5] = {mT, pT, betas, Tkin, n};

    // Define the integrand function wrapper
    auto integrandWrapper = [&](double xi) {
        return Integrand(&xi, integrandParams);
    };

    // Perform the integration using Boost
    using namespace boost::math::quadrature;
    gauss_kronrod<double, 61> integrator;
    double tolerance = 1e-6;
    double result = integrator.integrate(integrandWrapper, xmin, xmax, tolerance);

    // Return the final result multiplied by A
    return mT * A * result;
};

// double CostFunction(std::vector<std::vector<Data>> data, std::vector<std::vector<int>> indexes, double* pars) {

// };

}  // namespace Cillindrical

}  // namespace BoltzmannGibbs

#endif  // CILLINDRICALBOLTZMANNGIBBS_HPP
