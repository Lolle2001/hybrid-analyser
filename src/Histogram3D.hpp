#ifndef HISTOGRAM3D_HPP
#define HISTOGRAM3D_HPP

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <thread>
#include <vector>

#include "Messenger.hpp"
#include "StatisticsContainer.hpp"
#include "Utilities.hpp"

using PP = Utilities::PretyPrint;

// namespace AMPT {
namespace Statistics {
using Vector3DMap = std::vector<std::vector<std::vector<std::map<int, StatisticsContainer>>>>;
using Vector2DMap = std::vector<std::vector<std::map<int, StatisticsContainer>>>;
using Vector1DMap = std::vector<std::map<int, StatisticsContainer>>;
using Vector0DMap = std::map<int, StatisticsContainer>;

using Vector1DMapVector1D = std::vector<std::map<int, std::vector<StatisticsContainer>>>;
using Vector1DMapVector2D = std::vector<std::map<int, std::vector<std::vector<StatisticsContainer>>>>;
using MapVector1D = std::map<int, std::vector<StatisticsContainer>>;

using Vector3D = std::vector<std::vector<std::vector<StatisticsContainer>>>;
using Vector2D = std::vector<std::vector<StatisticsContainer>>;
using Vector1D = std::vector<StatisticsContainer>;

class Histogram3D {
   private:
    Vector1D Contents;

    int nx, ny, nz;

    std::map<int, int> IndexMapX;
    std::map<int, int> IndexMapY;
    std::map<int, int> IndexMapZ;
    double x_max;
    double x_min;
    double x_width;
    double y_max;
    double y_min;
    double y_width;
    double z_max;
    double z_min;
    double z_width;

    std::vector<double> EdgesX;
    std::vector<double> EdgesY;
    std::vector<double> EdgesZ;

    bool is_reversed = false;
    std::string Name;

   public:
    Histogram3D(){};
    // Histogram3D(int & nx_, int & ny_, int & nz_);
    Histogram3D(std::string Name_, std::vector<double> EdgesX_, std::vector<double> EdgesY_, std::vector<double> EdgesZ_);

    void Resize(int& nx_, int& ny_, int& nz_);

    void InitializeIndexMap();

    std::string& GetName();

    void AddEvent();
    void AddEventAverage();
    void Add(double& valx, double& valy, double& valz, double valcontent);
    void AddCurrent(double& valx, double& valy, double& valz, double valcontent);

    // void Convert();
    void PrintEdges(std::ostream& output);
    void PrintTotalSQR(std::ostream& output);
    void PrintTotal(std::ostream& output);
    void PrintCount(std::ostream& output);
    void PrintVariance(std::ostream& output);

    void ReverseEdges();

    void ReadEdges(std::string filename);
    void ReadTotalSQR(std::string filename);
    void ReadTotal(std::string filename);
    void ReadCount(std::string filename);

    int GetNbinsX() { return nx; };
    int GetNbinsY() { return ny; };
    int GetNbinsZ() { return nz; };

    double GetBinWidthX(int ix) {
        if (ix < nx) {
            return (EdgesX[ix + 1] - EdgesX[ix]);
        } else {
            return 0;
        }
    }
    double GetBinWidthY(int iy) {
        if (iy < ny) {
            return (EdgesY[iy + 1] - EdgesY[iy]);
        } else {
            return 0;
        }
    }
    double GetBinWidthZ(int iz) {
        if (iz < nz) {
            return (EdgesZ[iz + 1] - EdgesZ[iz]);
        } else {
            return 0;
        }
    }
    double GetBinMidX(int ix) {
        if (ix < nx) {
            return (EdgesX[ix + 1] + EdgesX[ix]) / 2;
        } else {
            return 0;
        }
    }
    double GetBinMidY(int iy) {
        if (iy < ny) {
            return (EdgesY[iy + 1] + EdgesY[iy]) / 2;
        } else {
            return 0;
        }
    }
    double GetBinMidZ(int iz) {
        if (iz < nz) {
            return (EdgesZ[iz + 1] + EdgesZ[iz]) / 2;
        } else {
            return 0;
        }
    }

    std::vector<double> GetEdgesX() {
        return EdgesX;
    }
    std::vector<double> GetEdgesY() {
        return EdgesY;
    }
    std::vector<double> GetEdgesZ() {
        return EdgesZ;
    }

    size_t GetIndex(int ix, int iy, int iz) {
        return iz + iy * nz + ix * ny * nz;
    }

    StatisticsContainer& GetContent(int ix, int iy, int iz) {
        return Contents[GetIndex(ix, iy, iz)];
    }

    StatisticsContainer& operator()(int& ix, int& iy, int& iz);
    // Vector1D& operator()(int& ix, int& iy);
    // Vector2D& operator()(int& ix);

    StatisticsContainer& operator()(double& valx, double& valy, double& valz);
    // Vector1D& operator()(double& valx, double& valy);
    // Vector2D& operator()(double& valx);

    void operator+=(Histogram3D const& obj);
};

}  // namespace Statistics
// }

#endif
