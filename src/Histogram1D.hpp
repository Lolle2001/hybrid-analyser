
#ifndef HISTOGRAM1D_HPP
#define HISTOGRAM1D_HPP

#include <map>
#include <vector>

#include "BinContainer.hpp"
#include "Messenger.hpp"
#include "StatisticsContainer.hpp"
#include "Utilities.hpp"

using PP = Utilities::PretyPrint;

// namespace AMPT {
namespace Statistics {

using Vector1D = std::vector<StatisticsContainer>;

class Histogram1D {
   private:
    Vector1D Contents;

    int nx;

    std::map<int, int> IndexMapX;

    double x_max;
    double x_min;
    double x_width;

    std::vector<double> EdgesX;

   public:
    Histogram1D(){};
    // Histogram1D(int & nx_);
    Histogram1D(std::vector<double> EdgesX_);

    Histogram1D(std::shared_ptr<BinContainer> bincontainerX);

    void
    Resize(int& nx_);

    void InitializeIndexMap();

    void AddEvent();

    void Add(double& valx, double valcontent);

    void AddCurrent(double& valx, double valcontent);

    void PrintCount(std::ostream& output);

    void PrintTotalSQR(std::ostream& output);

    void PrintTotal(std::ostream& output);

    void PrintEdges(std::ostream& output);

    void ReadEdges(std::string filename);
    void ReadTotalSQR(std::string filename);
    void ReadTotal(std::string filename);
    void ReadCount(std::string filename);

    StatisticsContainer& operator()(int& ix);

    StatisticsContainer& operator()(double& valx);

    void operator+=(Histogram1D const& obj);
};
}  // namespace Statistics
// }

#endif