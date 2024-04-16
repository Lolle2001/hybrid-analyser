
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

    int nx, ny, nz;

    std::map<int, int> IndexMapX;

    double x_max;
    double x_min;
    double x_width;

    std::vector<double> EdgesX;

    double y_max;
    double y_min;
    double z_max;
    double z_min;

    bool thirdaxis = false;
    bool secondaxis = false;

    std::vector<double> EdgesY;

    std::vector<double> EdgesZ;

    std::string Name;

   public:
    Histogram1D(){};
    // Histogram1D(int & nx_);
    Histogram1D(std::string Name_, std::vector<double> EdgesX_);
    Histogram1D(std::string Name_, std::vector<double> EdgesX_, std::vector<double> EdgesY_);
    Histogram1D(std::string Name_, std::vector<double> EdgesX_, std::vector<double> EdgesY_, std::vector<double> EdgesZ_);
    // Histogram1D(std::shared_ptr<BinContainer> bincontainerX);

    void
    Resize(int& nx_);

    void InitializeIndexMap();

    void AddEvent();
    void AddEventAverage();

    void Add(double& valx, double valcontent);
    void Add(double& valx, double& valy, double valcontent);
    void Add(double& valx, double& valy, double& valz, double valcontent);
    void AddCurrent(double& valx, double valcontent);
    void AddCurrent(double& valx, double& valy, double valcontent);
    void AddCurrent(double& valx, double& valy, double& valz, double valcontent);

    std::string& GetName();

    void PrintCount(std::ostream& output);

    void PrintTotalSQR(std::ostream& output);

    void PrintTotal(std::ostream& output);

    void PrintEdges(std::ostream& output);

    void ReverseEdges();

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