#ifndef CILLINDRICALTSALLIS_HPP
#define CILLINDRICALTSALLIS_HPP

#include <TMath.h>

#include <boost/math/quadrature/gauss_kronrod.hpp>
#include <boost/math/special_functions/bessel.hpp>

namespace Tsallis {
namespace Cillindrical {
double Integrand(double *x, double *par) {
    double xi = x[0];
    double phi = x[1];
    double y = x[2];

    double mT = par[0];
    double pT = par[1];
    double betas = par[2];
    double Tkin = par[3];
    double n = par[4];
    double q = par[5];
    double yb = par[6];

    double yexp = TMath::Exp(TMath::Sqrt(yb * yb - y * y));
    double rhoarg = betas * TMath::Power(xi, n);
    double rho = TMath::ATanH(rhoarg);
    double ET = mT * TMath::CosH(y) * TMath::CosH(rho) - pT * TMath::SinH(rho) * TMath::Cos(phi);
    double phiexparg = 1 + ((q - 1) / (Tkin)) * ET;
    double phiexp = TMath::Power(phiexparg, 1 / (1 - q));

    return xi * yexp * phiexp;
}

double Function(double *x, double *par) {
    double pT = x[0];
    double A = par[0];
    double Tkin = par[1];
    double m0 = par[2];
    double betas = par[3];
    double n = par[4];
    double q = par[5];
    double yb = par[6];
    double mT = std::sqrt(m0 * m0 + pT * pT);

    double integrandparams[7] = {mT, pT, betas, Tkin, n, q, yb};

    auto integrand_wrapped = [&](double xi, double phi, double y) {
        double vars[3] = {xi, phi, y};
        return Integrand(vars, integrandparams);
    };

    auto integration = [&integrand_wrapped](double xi_min, double xi_max,
                                            double phi_min, double phi_max,
                                            double y_min, double y_max) {
        constexpr int points = 10;  // Number of points for Gaussian quadrature
        double result = 0.0;
        boost::math::quadrature::gauss<double, points> integrator;

        result = integrator.integrate([&](double xi) {
            return integrator.integrate([&](double phi) {
                return integrator.integrate([&](double y) {
                    return integrand_wrapped(xi, phi, y);
                },
                                            y_min, y_max);
            },
                                        phi_min, phi_max);
        },
                                      xi_min, xi_max);

        return result;
    };

    double xi_min = 0.0, xi_max = 1.0;
    double phi_min = 0.0, phi_max = 2 * boost::math::constants::pi<double>();
    double y_min = -yb, y_max = yb;

    return mT * A * integration(xi_min, xi_max, phi_min, phi_max, y_min, y_max);
}
}  // namespace Cillindrical

namespace Cillindrical_2 {
double Integrand(double *x, double *par) {
    double xi = x[0];
    double phi = x[1];

    double mT = par[0];
    double pT = par[1];
    double betas = par[2];
    double Tkin = par[3];
    double n = par[4];
    double q = par[5];

    double rhoarg = betas * TMath::Power(xi, n);
    double rho = TMath::ATanH(rhoarg);
    double ET = mT * TMath::CosH(rho) - pT * TMath::SinH(rho) * TMath::Cos(phi);
    double phiexparg = 1 + ((q - 1) / (Tkin)) * ET;
    double phiexp = TMath::Power(phiexparg, 1 / (1 - q));

    return xi * phiexp;
}

double Function(double *x, double *par) {
    double pT = x[0];
    double A = par[0];
    double Tkin = par[1];
    double m0 = par[2];
    double betas = par[3];
    double n = par[4];
    double q = par[5];

    double mT = std::sqrt(m0 * m0 + pT * pT);

    double integrandparams[6] = {mT, pT, betas, Tkin, n, q};

    auto integrand_wrapped = [&](double xi, double phi) {
        double vars[2] = {xi, phi};
        return Integrand(vars, integrandparams);
    };

    auto integration = [&integrand_wrapped](double xi_min, double xi_max,
                                            double phi_min, double phi_max) {
        constexpr int points = 10;  // Number of points for Gaussian quadrature
        double result = 0.0;
        boost::math::quadrature::gauss<double, points> integrator;

        result = integrator.integrate([&](double xi) {
            return integrator.integrate([&](double phi) {
                return integrand_wrapped(xi, phi);
            },
                                        phi_min, phi_max);
        },
                                      xi_min, xi_max);

        return result;
    };

    const double xi_min = 0.0;
    const double xi_max = 1.0;
    const double phi_min = -boost::math::constants::pi<double>();
    const double phi_max = boost::math::constants::pi<double>();

    return mT * A * integration(xi_min, xi_max, phi_min, phi_max);
}
}  // namespace Cillindrical_2

}  // namespace Tsallis

#endif