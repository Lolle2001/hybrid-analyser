// Copyright (C) 2024 Lieuwe Huisman
#ifndef EVOLUTION_AMPT_UTILITIES_HPP
#define EVOLUTION_AMPT_UTILITIES_HPP

#include <cmath>
#include <fstream>
#include <limits>
#include <nlohmann/json.hpp>
#include <ostream>
#include <sstream>
#include <vector>

namespace AMPT {
namespace Evolution {
struct Particle {
    int ParticlePythiaID;
    int ParticleLabel;
    double PosX;
    double PosY;
    double PosZ;
    double MomX;
    double MomY;
    double MomZ;
    double Mass;
    double Energy;
    double Rapidity;
    double Phi;
    double Theta;
    double SpacetimeRapidity;
    double PosT;

    Particle(){};

    void CalculateEnergy() {
        Energy = std::sqrt(MomX * MomX + MomY * MomY + MomZ * MomZ + Mass * Mass);
    }

    void CalculateRapidity() {
        Rapidity = std::atanh(MomZ / Energy);
    }

    void CalculateSpaceTimeRapidity() {
        SpacetimeRapidity = std::atanh(PosZ / std::sqrt(PosX * PosX + PosY * PosY + PosZ * PosZ));
    }

    void CalculatePhi() {
        Phi = std::atan2(PosY, PosX);
    }

    void CalculateTheta() {
        Theta = std::acos(PosZ / std::sqrt(PosX * PosX + PosY * PosY + PosZ * PosZ));
    }
};

std::istream &operator>>(std::istream &input, Particle &particle) {
    input >> particle.ParticleLabel;
    input >> particle.PosX;
    input >> particle.PosY;
    input >> particle.PosZ;
    input >> particle.MomX;
    input >> particle.MomY;
    input >> particle.MomZ;
    input >> particle.Mass;
    return input;
}

std::ostream &operator<<(std::ostream &output, Particle &particle) {
    // output << std::setw(13) << std::right << particle.ParticlePythiaID << " ";
    output << std::setw(9) << std::right << particle.ParticleLabel << " ";
    output << std::setw(9) << std::right << particle.PosX << " ";
    output << std::setw(9) << std::right << particle.PosY << " ";
    output << std::setw(9) << std::right << particle.PosZ << " ";
    output << std::setw(9) << std::right << particle.MomX << " ";
    output << std::setw(9) << std::right << particle.MomY << " ";
    output << std::setw(9) << std::right << particle.MomZ << " ";
    output << std::setw(9) << std::right << particle.Mass;
    return output;
}

class HistogramS2D {
   private:
    double min_x;
    double max_x;
    size_t n_x;
    double min_y;
    double max_y;
    size_t n_y;
    double min_z;
    double max_z;

    double dx;
    double dy;

    std::vector<std::vector<double>> contents;
    std::vector<std::vector<size_t>> counts;

   public:
    HistogramS2D(double min_x, double max_x, size_t n_x, double min_y, double max_y, size_t n_y) : min_x(min_x), max_x(max_x), n_x(n_x), min_y(min_y), max_y(max_y), n_y(n_y) {
        contents.resize(n_x, std::vector<double>(n_y, 0));
        counts.resize(n_x, std::vector<size_t>(n_y, 0));
        dx = (max_x - min_x) / (n_x);
        dy = (max_y - min_y) / (n_y);
    }
    HistogramS2D(double min_x, double max_x, size_t n_x, double min_y, double max_y, size_t n_y, double min_z, double max_z) : min_x(min_x), max_x(max_x), n_x(n_x), min_y(min_y), max_y(max_y), n_y(n_y), min_z(min_z), max_z(max_z) {
        contents.resize(n_x, std::vector<double>(n_y, 0));
        counts.resize(n_x, std::vector<size_t>(n_y, 0));
        dx = (max_x - min_x) / (n_x);
        dy = (max_y - min_y) / (n_y);
    }

    void Add(double x, double y, double val) {
        if (x >= min_x && x < max_x && y >= min_y && y < max_y) {
            int ix = static_cast<int>((x - min_x) / (dx));
            int iy = static_cast<int>((y - min_y) / (dy));
            contents[ix][iy] += val;
            counts[ix][iy]++;
        }
    }

    void Add(double x, double y, double z, double val) {
        if (x >= min_x && x < max_x && y >= min_y && y < max_y && z >= min_z && z < max_z) {
            int ix = static_cast<int>((x - min_x) / (dx));
            int iy = static_cast<int>((y - min_y) / (dy));
            contents[ix][iy] += val;
            counts[ix][iy]++;
        }
    }

    void CalculateAverage() {
        for (index_t ix = 0; ix < n_x; ++ix) {
            for (index_t iy = 0; iy < n_y; ++iy) {
                if (counts[ix][iy] > 0) {
                    contents[ix][iy] /= counts[ix][iy];
                }
            }
        }
    }

    void PrintContents(std::ostream &output) {
        output << "#" << " " << min_x << " " << max_x << " " << dx << " " << n_x << "\n";
        output << "#" << " " << min_y << " " << max_y << " " << dy << " " << n_y << "\n";
        for (index_t ix = 0; ix < n_x; ++ix) {
            for (index_t iy = 0; iy < n_y; ++iy) {
                output << contents[ix][iy] << " ";
            }
            output << "\n";
        }
    }
};

class HistogramS3D {
   private:
    double min_x;
    double max_x;
    size_t n_x;
    double min_y;
    double max_y;
    size_t n_y;
    double min_z;
    double max_z;
    size_t n_z;

    double dx;
    double dy;
    double dz;

    std::vector<double> contents;
    std::vector<size_t> counts;

   public:
    HistogramS3D(
        double min_x, double max_x, size_t n_x,
        double min_y, double max_y, size_t n_y,
        double min_z, double max_z, size_t n_z) : min_x(min_x), max_x(max_x), n_x(n_x), min_y(min_y), max_y(max_y), n_y(n_y), min_z(min_z), max_z(max_z), n_z(n_z) {
        contents.resize(n_x * n_y * n_z, 0);
        counts.resize(n_x * n_y * n_z, 0);
        dx = (max_x - min_x) / n_x;
        dy = (max_y - min_y) / n_y;
        dz = (max_z - min_z) / n_z;
    }

    void Add(double x, double y, double z, double val) {
        if (x >= min_x && x < max_x && y >= min_y && y < max_y && z >= min_z && z < max_z) {
            int ix = static_cast<int>((x - min_x) / dx);
            int iy = static_cast<int>((y - min_y) / dy);
            int iz = static_cast<int>((z - min_z) / dz);
            size_t index = iz + n_z * (iy + n_y * ix);
            contents[index] += val;
            counts[index]++;
        }
    }

    void PrintContents(std::ostream &output) {
        output << "#" << " " << min_x << " " << max_x << " " << dx << " " << n_x << "\n";
        output << "#" << " " << min_y << " " << max_y << " " << dy << " " << n_y << "\n";
        output << "#" << " " << min_z << " " << max_z << " " << dz << " " << n_z << "\n";
        for (size_t ix = 0; ix < n_x; ++ix) {
            for (size_t iy = 0; iy < n_y; ++iy) {
                for (size_t iz = 0; iz < n_z; ++iz) {
                    size_t index = iz + n_z * (iy + n_y * ix);
                    output << ix << " " << iy << " " << iz << " " << contents[index] << "\n";
                }
                // output << "\n";
            }
        }
    }
};

template <class T>
void json_to_parameter(const nlohmann::json &j, const std::string key, T &target) {
    if (j.contains(key)) {
        j.at(key).get_to(target);
    } else {
        std::cout << "[WARNING]" << "JSON file does contain parameter with key: " << key << std::endl;
    }
};

struct Gridsettings {
    double xmin;
    double xmax;
    double dx;
    size_t nx;
    double ymin;
    double ymax;
    double dy;
    size_t ny;
    double zmin;
    double zmax;
    double dz;
    size_t nz;
    double dvolume;

    void SetVolumeElement() {
        dvolume = dx * dy * dz;
    }
    void SetProperties() {
        dx = (xmax - xmin) / (nx);
        dy = (ymax - ymin) / (ny);
        dz = (zmax - zmin) / (nz);
        dvolume = dx * dy * dz;
    }
};

std::ostream &operator<<(std::ostream &output, const Gridsettings &grid) {
    output << grid.dvolume << " " << grid.nx * grid.ny * grid.nz << "\n";
    output << grid.xmin << " " << grid.xmax << " " << grid.dx << " " << grid.nx << "\n";
    output << grid.ymin << " " << grid.ymax << " " << grid.dy << " " << grid.ny << "\n";
    output << grid.zmin << " " << grid.zmax << " " << grid.dz << " " << grid.nz << "\n";
    return output;
}

std::istringstream CGetline(std::ifstream &file, std::string &str) {
    std::getline(file, str);
    return std::istringstream(str);
}

std::vector<double> linspace(double min, double max, size_t num) {
    double delta = (max - min) / (num);
    std::vector<double> range(num);
    for (int i = 0; i < num; ++i) {
        range[i] = min + delta * i;
    }
    return range;
}

int getindex(double val, double &min, double &delta) {
    return static_cast<int>((val - min) / (delta));
}

std::ifstream &GotoLine(std::ifstream &file, unsigned int num) {
    file.seekg(std::ios::beg);
    for (int i = 0; i < num - 1; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return file;
}

}  // namespace Evolution
}  // namespace AMPT

#endif