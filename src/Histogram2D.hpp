#ifndef HISTOGRAM2D_HPP
#define HISTOGRAM2D_HPP

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

class Histogram2D {
   private:
    Vector2D Contents;

    int nx, ny, nz;

    std::map<int, int> IndexMapX;
    std::map<int, int> IndexMapY;

    double x_max;
    double x_min;
    double x_width;
    double y_max;
    double y_min;
    double y_width;
    double z_max;
    double z_min;

    std::vector<double> EdgesX;
    std::vector<double> EdgesY;
    bool thirdaxis = false;
    std::vector<double> EdgesZ;
    std::string Name;

   public:
    Histogram2D(){};
    // Histogram3D(int & nx_, int & ny_, int & nz_);
    Histogram2D(std::vector<double> EdgesX_, std::vector<double> EdgesY_);
    Histogram2D(std::vector<double> EdgesX_, std::vector<double> EdgesY_, std::vector<double> EdgesZ_);
    Histogram2D(std::string Name_, std::vector<double> EdgesX_, std::vector<double> EdgesY_, std::vector<double> EdgesZ_);
    void Resize(int& nx_, int& ny_);

    void InitializeIndexMap();

    void AddEvent();
    void AddEventAverage();
    void Add(double& valx, double& valy, double valcontent);
    void Add(double& valx, double& valy, double& valz, double valcontent);
    void AddCurrent(double& valx, double& valy, double valcontent);
    void AddCurrent(double& valx, double& valy, double& valz, double valcontent);

    std::string& GetName();

    // void Convert();
    void PrintEdges(std::ostream& output);
    void PrintTotalSQR(std::ostream& output);
    void PrintTotal(std::ostream& output);
    void PrintCount(std::ostream& output);

    void ReadEdges(std::string filename);
    void ReadTotalSQR(std::string filename);
    void ReadTotal(std::string filename);
    void ReadCount(std::string filename);

    int GetNbinsX() { return nx; };
    int GetNbinsY() { return ny; };

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

    std::vector<double> GetEdgesX() {
        return EdgesX;
    }
    std::vector<double> GetEdgesY() {
        return EdgesY;
    }

    StatisticsContainer& operator()(int& ix, int& iy);
    Vector1D& operator()(int& ix);

    StatisticsContainer& operator()(double& valx, double& valy);
    Vector1D& operator()(double& valx);

    void operator+=(Histogram2D const& obj);
};

}  // namespace Statistics
// }

#endif
