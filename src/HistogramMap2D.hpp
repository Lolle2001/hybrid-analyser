// Copyright (C) 2024 Lieuwe Huisman
#ifndef HISTOGRAMMAP2D_HPP
#define HISTOGRAMMAP2D_HPP

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

namespace Statistics {
using Vector3DMap = std::vector<std::vector<std::vector<std::map<int, StatisticsContainer>>>>;
using Vector2DMap = std::vector<std::vector<std::map<int, StatisticsContainer>>>;
using Vector1DMap = std::vector<std::map<int, StatisticsContainer>>;
using Vector0DMap = std::map<int, StatisticsContainer>;

using Vector1DMapVector1D = std::vector<std::map<int, std::vector<StatisticsContainer>>>;
using Vector1DMapVector2D = std::vector<std::map<int, std::vector<std::vector<StatisticsContainer>>>>;
using MapVector1D = std::map<int, std::vector<StatisticsContainer>>;
using MapVector2D = std::map<int, std::vector<std::vector<StatisticsContainer>>>;

class HistogramMap2D {
   private:
    Vector2DMap Contents;
    MapVector2D ContentsConverted;

    size_t nx, ny;

    std::map<int, int> IndexMapX;
    std::map<int, int> IndexMapY;

    double x_max;
    double x_min;
    double x_width;
    double y_max;
    double y_min;
    double y_width;

    std::vector<double> EdgesX;
    std::vector<double> EdgesY;

    std::string Name;

   public:
    HistogramMap2D(){};
    // HistogramMap3D(int & nx_, int & ny_, int & nz_);
    HistogramMap2D(std::string Name_, std::vector<double> EdgesX_, std::vector<double> EdgesY_);

    void Resize(size_t& nx_, size_t& ny_);

    void InitializeIndexMap();

    void AddEvent();
    void AddEventAverage();

    void Add(double& valx, double& valy, int& key, double valcontent);
    void AddCurrent(double& valx, double& valy, int& key, double valcontent);

    void Convert();

    std::string& GetName();

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

    double GetBinWidthX(index_t ix) {
        if (ix < nx) {
            return (EdgesX[ix + 1] - EdgesX[ix]);
        } else {
            return 0;
        }
    }
    double GetBinWidthY(index_t iy) {
        if (iy < ny) {
            return (EdgesY[iy + 1] - EdgesY[iy]);
        } else {
            return 0;
        }
    }

    double GetBinMidX(index_t ix) {
        if (ix < nx) {
            return (EdgesX[ix + 1] + EdgesX[ix]) / 2;
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

    StatisticsContainer& operator()(int& ix, int& iy, int& key);
    Vector0DMap& operator()(int& ix, int& iy);
    Vector1DMap& operator()(int& ix);

    StatisticsContainer& operator()(double& valx, double& valy, int& key);
    Vector0DMap& operator()(double& valx, double& valy);
    Vector1DMap& operator()(double& valx);

    void operator+=(HistogramMap2D const& obj);
};

}  // namespace Statistics
// }

#endif
