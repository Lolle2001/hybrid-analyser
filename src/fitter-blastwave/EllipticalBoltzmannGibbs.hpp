// Copyright (C) 2024 Lieuwe Huisman
#ifndef ELLIPTICALBOLTZMANNGIBBS_HPP
#define ELLIPTICALBOLTZMANNGIBBS_HPP

#include <TMath.h>

#include <boost/math/quadrature/gauss_kronrod.hpp>
#include <boost/math/special_functions/bessel.hpp>

#include "Data.hpp"

struct BoltzmannGibbsElliptical
{
    double operator()()
    {
    }
};

namespace BoltzmannGibbs
{
    namespace Elliptical
    {
        double Integrand(double *x, double *par)
        {
            double rhat = x[0];
            double phihat = x[1];

            double mT = par[0];
            double pT = par[1];
            double Tkin = par[2];
            double rho0 = par[3];
            double rho2 = par[4];
            double RxRy = par[5];

            double phib = TMath::ATan(RxRy * TMath::Tan(phihat));
            double rho = rho0 + rho2 * TMath::Cos(2 * phib);

            // double arg0 = betas * std::pow(xi, n);
            // double rho = std::atanh(arg0);
            // double arg1 = mT * std::cosh(rho) / Tkin;
            // double arg2 = pT * std::sinh(rho) / Tkin;
            // double k1 = boost::math::cyl_bessel_k(1, arg1);
            // double i0 = boost::math::cyl_bessel_i(0, arg2);

            double arg1 = mT * TMath::CosH(rhat * rho) / Tkin;
            double arg2 = pT * TMath::SinH(rhat * rho) / Tkin;
            double k1 = TMath::BesselK1(arg1);
            double i0 = TMath::BesselI0(arg2);

            return rhat * k1 * i0;
        }

        double Function(double *x, double *par)
        {
            double pT = x[0];
            double A = par[0];
            double Tkin = par[1];
            double m0 = par[2];
            double rho0 = par[3];
            double rho2 = par[4];
            double RxRy = par[5];
            double mT = std::sqrt(m0 * m0 + pT * pT);

            // Integrand parameters
            double integrandParams[6] = {mT, pT, Tkin, rho0, rho2, RxRy};

            // Define the integrand function wrapper
            auto integrand_wrapped = [&](double rhat, double phihat)
            {
                double vars[2] = {rhat, phihat};
                return Integrand(vars, integrandParams);
            };

            // Perform the integration using Boost
            auto integration = [&integrand_wrapped](double rhat_min, double rhat_max,
                                                    double phihat_min, double phihat_max)
            {
                constexpr int points = 10; // Number of points for Gaussian quadrature
                double result = 0.0;
                boost::math::quadrature::gauss<double, points> integrator;

                result = integrator.integrate([&](double rhat)
                                              { return integrator.integrate([&](double phihat)
                                                                            { return integrand_wrapped(rhat, phihat); },
                                                                            phihat_min, phihat_max); },
                                              rhat_min, rhat_max);

                return result;
            };

            const double rhat_min = 0.0;
            const double rhat_max = 1.0;
            const double phihat_min = 0;
            const double phihat_max = 2 * boost::math::constants::pi<double>();

            // Return the final result multiplied by A
            return mT * A * integration(rhat_min, rhat_max, phihat_min, phihat_max);
        };
    } // namespace Elliptical
    namespace Elliptical_2
    {
        double Integrand(double *x, double *par)
        {
            double rhat = x[0];
            double phihat = x[1];

            double mT = par[0];
            double pT = par[1];
            double Tkin = par[2];
            double rho0 = par[3];
            double rho2 = par[4];
            double RxRy = par[5];

            double phib = TMath::ATan(RxRy * TMath::Tan(phihat)) + TMath::Pi() * TMath::Floor((phihat / TMath::Pi() + 0.5));

            double rho = rhat * (rho0 + rho2 * TMath::Cos(2 * phib));

            // double arg0 = betas * std::pow(xi, n);
            // double rho = std::atanh(arg0);
            // double arg1 = mT * std::cosh(rho) / Tkin;
            // double arg2 = pT * std::sinh(rho) / Tkin;
            // double k1 = boost::math::cyl_bessel_k(1, arg1);
            // double i0 = boost::math::cyl_bessel_i(0, arg2);

            double arg1 = mT * TMath::CosH(rho) / Tkin;
            double arg2 = pT * TMath::SinH(rho) / Tkin;
            double k1 = TMath::BesselK1(arg1);
            double i0 = TMath::BesselI0(arg2);

            return rhat * k1 * i0;
        }

        double Function(double *x, double *par)
        {
            double pT = x[0];
            double A = par[0];
            double Tkin = par[1];
            double m0 = par[2];
            double rho0 = par[3];
            double rho2 = par[4];
            double RxRy = par[5];
            double mT = std::sqrt(m0 * m0 + pT * pT);

            // Integrand parameters
            double integrandParams[6] = {mT, pT, Tkin, rho0, rho2, RxRy};

            // Define the integrand function wrapper
            auto integrand_wrapped = [&](double rhat, double phihat)
            {
                double vars[2] = {rhat, phihat};
                return Integrand(vars, integrandParams);
            };

            // Perform the integration using Boost
            auto integration = [&integrand_wrapped](double rhat_min, double rhat_max,
                                                    double phihat_min, double phihat_max)
            {
                constexpr int points = 10; // Number of points for Gaussian quadrature
                double result = 0.0;
                boost::math::quadrature::gauss<double, points> integrator;

                result = integrator.integrate([&](double rhat)
                                              { return integrator.integrate([&](double phihat)
                                                                            { return integrand_wrapped(rhat, phihat); },
                                                                            phihat_min, phihat_max); },
                                              rhat_min, rhat_max);

                return result;
            };

            const double rhat_min = 0.0;
            const double rhat_max = 1.0;
            const double phihat_min = 0;
            const double phihat_max = 2 * boost::math::constants::pi<double>();

            // Return the final result multiplied by A
            return mT * A * integration(rhat_min, rhat_max, phihat_min, phihat_max);
        };
    } // namespace Elliptical_2
} // namespace BoltzmannGibbs

#endif