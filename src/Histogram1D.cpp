#include "Histogram1D.hpp"
// namespace AMPT {
namespace Statistics {

//  Histogram1D::Histogram1D(int & nx_) : nx(nx_){
//             Resize(nx);
//         };

Histogram1D::Histogram1D(
    std::vector<double> EdgesX_) : EdgesX(EdgesX_)

{
    nx = EdgesX.size() - 1;

    Resize(nx);
    InitializeIndexMap();
}

Histogram1D::Histogram1D(std::shared_ptr<BinContainer> bincontainerX) {
    nx = bincontainerX->n;
    Resize(nx);
    x_width = bincontainerX->width;
    x_max = bincontainerX->max;
    x_min = bincontainerX->min;
    EdgesX = bincontainerX->Edges;
    IndexMapX = bincontainerX->IndexMap;
}

void Histogram1D::Resize(int& nx_) {
    Contents.resize(nx_);
}

void Histogram1D::AddEvent() {
    for (int ix = 0; ix < nx; ++ix) {
        Contents[ix].AddEvent();
    }
}

void Histogram1D::Add(double& valx, double valcontent) {
    if (valx >= x_min && valx < x_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        Contents[ix].Add(valcontent);
    }
}

void Histogram1D::AddCurrent(double& valx, double valcontent) {
    if (valx >= x_min && valx < x_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        Contents[ix].AddCurrent(valcontent);
    }
}

void Histogram1D::InitializeIndexMap() {
    x_max = EdgesX.back();
    x_min = EdgesX.front();

    std::vector<double> xwidths(nx);

    for (int ix = 0; ix < nx; ++ix) {
        xwidths[ix] = EdgesX[ix + 1] - EdgesX[ix];
        // std::cout << xwidths[ix] << std::endl;
    }

    double x_smallest_width = xwidths[0];

    double x_temp_width;

    for (int ix = 0; ix < nx; ++ix) {
        for (int jx = ix + 1; jx < nx; ++jx) {
            x_temp_width = Utilities::igcd(xwidths[ix], xwidths[jx], 0.001);
            if (x_temp_width < x_smallest_width) {
                x_smallest_width = x_temp_width;
            }
        }
    }

    x_width = x_smallest_width;

    int temp_nx = static_cast<int>((x_max - x_min) / x_width);

    double x;

    for (int ix = 0; ix < temp_nx; ++ix) {
        x = (x_min + ix * x_width + x_width * 0.5);

        for (int jx = 0; jx < nx; ++jx) {
            if (x > EdgesX[jx] && x < EdgesX[jx + 1]) {
                IndexMapX[ix] = jx;
            }
        }
    }

    xwidths.clear();
}

StatisticsContainer& Histogram1D::operator()(int& ix) {
    return Contents[ix];
}

StatisticsContainer& Histogram1D::operator()(double& valx) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];

    return Contents[ix];
}

void Histogram1D::operator+=(Histogram1D const& obj) {
    if (nx == obj.nx) {
        for (int ix = 0; ix < nx; ++ix) {
            Contents[ix] += obj.Contents[ix];
        }
    } else {
        printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
        printf("%s\n", "Cannot add two HistogramMaps of different sizes!");
    }
}

void Histogram1D::PrintCount(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        output << ix << " ";
        output << Contents[ix].EntryCount << "\n";
    }
}

void Histogram1D::PrintTotal(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        output << ix << " ";
        output << Contents[ix].Total << "\n";
    }
}

void Histogram1D::PrintTotalSQR(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        output << ix << " ";
        output << Contents[ix].TotalSQR << "\n";
    }
}

void Histogram1D::PrintEdges(std::ostream& output) {
    output << "nbins(x) = " << nx << "\n";
    output << "edges(x) = ";
    for (int ix = 0; ix <= nx; ++ix) {
        output << EdgesX[ix] << " ";
    }
    output << "\n";
}
void Histogram1D::ReadEdges(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;
    std::string dummy1;
    std::string dummy2;
    std::string dummy3;
    double edge;
    file.open(filename, std::ios::in);

    std::getline(file, line);
    iss = std::istringstream(line);

    iss >> dummy1 >> dummy2 >> nx;

    std::getline(file, line);
    iss = std::istringstream(line);

    iss >> dummy1 >> dummy2;

    while (iss >> edge) {
        EdgesX.push_back(edge);
    }

    file.close();
    Resize(nx);
    InitializeIndexMap();
}
void Histogram1D::ReadTotalSQR(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;
    std::string dummy1;
    double value;

    file.open(filename, std::ios::in);
    for (int ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        iss = std::istringstream(line);
        iss >> dummy1 >> Contents[ix].TotalSQR;
    }
    file.close();
}
void Histogram1D::ReadTotal(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;
    std::string dummy1;
    double value;

    file.open(filename, std::ios::in);
    for (int ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        iss = std::istringstream(line);
        iss >> dummy1 >> Contents[ix].Total;
    }
    file.close();
}
void Histogram1D::ReadCount(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;
    std::string dummy1;
    double value;

    file.open(filename, std::ios::in);
    for (int ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        iss = std::istringstream(line);
        iss >> dummy1 >> Contents[ix].EntryCount;
    }
    file.close();
}
}  // namespace Statistics
   // }