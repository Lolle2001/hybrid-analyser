#include "Histogram1D.hpp"
// namespace AMPT {
namespace Statistics {

//  Histogram1D::Histogram1D(int & nx_) : nx(nx_){
//             Resize(nx);
//         };

Histogram1D::Histogram1D(
    std::string Name_, std::vector<double> EdgesX_) : Name(Name_), EdgesX(EdgesX_)

{
    nx = EdgesX.size() - 1;

    Resize(nx);
    InitializeIndexMap();
}

Histogram1D::Histogram1D(std::string Name_,
                         std::vector<double> EdgesX_,
                         std::vector<double> EdgesY_) : Name(Name_), EdgesX(EdgesX_), EdgesY(EdgesY_) {
    nx = EdgesX.size() - 1;
    secondaxis = true;

    ny = 1;
    Resize(nx);
    InitializeIndexMap();
}

Histogram1D::Histogram1D(std::string Name_,
                         std::vector<double> EdgesX_,
                         std::vector<double> EdgesY_,
                         std::vector<double> EdgesZ_) : Name(Name_), EdgesX(EdgesX_), EdgesY(EdgesY_), EdgesZ(EdgesZ_) {
    nx = EdgesX.size() - 1;
    secondaxis = true;
    thirdaxis = true;
    ny = 1;
    nz = 1;
    Resize(nx);
    InitializeIndexMap();
}

std::string& Histogram1D::GetName() {
    return Name;
}

void Histogram1D::ReverseEdges() {
    for (auto& entry : IndexMapX) {
        entry.second = nx - 1 - entry.second;
    }
}

void Histogram1D::Resize(int& nx_) {
    Contents.resize(nx_);
}

void Histogram1D::AddEvent() {
    for (int ix = 0; ix < nx; ++ix) {
        Contents[ix].AddEvent();
    }
}

void Histogram1D::AddEventAverage() {
    for (int ix = 0; ix < nx; ++ix) {
        Contents[ix].AddEventSpecial();
    }
}

void Histogram1D::Add(double& valx, double valcontent) {
    if (valx > x_min && valx <= x_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        Contents[ix].Add(valcontent);
    }
}

void Histogram1D::AddCurrent(double& valx, double valcontent) {
    if (valx > x_min && valx <= x_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        Contents[ix].AddCurrent(valcontent);
    }
}

void Histogram1D::Add(double& valx, double& valy, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];

        Contents[ix].Add(valcontent);
    }
}

void Histogram1D::AddCurrent(double& valx, double& valy, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];

        Contents[ix].AddCurrent(valcontent);
    }
}

void Histogram1D::Add(double& valx, double& valy, double& valz, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max && valz >= z_min && valz < z_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];

        Contents[ix].Add(valcontent);
    }
}

void Histogram1D::AddCurrent(double& valx, double& valy, double& valz, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max && valz >= z_min && valz < z_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];

        Contents[ix].AddCurrent(valcontent);
    }
}

void Histogram1D::InitializeIndexMap() {
    if (EdgesX[1] - EdgesX[0] > 0) {
        x_max = EdgesX.back();
        x_min = EdgesX.front();
    } else {
        x_max = EdgesX.front();
        x_min = EdgesX.back();
    }
    if (secondaxis) {
        y_max = EdgesY.back();
        y_min = EdgesY.front();
    }
    if (thirdaxis) {
        z_max = EdgesZ.back();
        z_min = EdgesZ.front();
    }

    std::vector<double> xwidths(nx);

    // Calculate the width of each bin
    for (int ix = 0; ix < nx; ++ix) {
        xwidths[ix] = std::abs(EdgesX[ix + 1] - EdgesX[ix]);
    }

    // Find the smallest width for the bins
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

    // Assign the smallest width to the bins
    x_width = x_smallest_width;

    // Calculate the number of bins
    int temp_nx = static_cast<int>((x_max - x_min) / x_width);

    // Assign index mappings for each bin
    double x;
    for (int ix = 0; ix < temp_nx; ++ix) {
        x = (x_min + ix * x_width + x_width * 0.5);
        for (int jx = 0; jx < nx; ++jx) {
            if ((EdgesX[0] < EdgesX[1] && x > EdgesX[jx] && x < EdgesX[jx + 1]) ||
                (EdgesX[0] > EdgesX[1] && x < EdgesX[jx] && x > EdgesX[jx + 1])) {
                IndexMapX[ix] = jx;
            }
        }
    }

    // Clear the temporary vector
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
        // std::cout << nx << std::endl;
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
        output << Contents[ix].EntryCount << "\n";
    }
}

void Histogram1D::PrintTotal(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        output << Contents[ix].Total << "\n";
    }
}

void Histogram1D::PrintTotalSQR(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
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
    if (secondaxis) {
        output << "nbins(y) = " << ny << "\n";
        output << "edges(y) = ";
        for (int iy = 0; iy <= ny; ++iy) {
            output << EdgesY[iy] << " ";
        }
        output << "\n";
    }
    if (thirdaxis) {
        output << "nbins(z) = " << nz << "\n";
        output << "edges(z) = ";
        for (int iz = 0; iz <= nz; ++iz) {
            output << EdgesZ[iz] << " ";
        }
        output << "\n";
    }
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