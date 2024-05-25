#include <fstream>

#include "CillindricalBoltzmannGibbs.hpp"

int main(int argc, char* argv[]) {
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
    return 0;
}