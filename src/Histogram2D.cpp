#include "Histogram2D.hpp"

// namespace AMPT {
namespace Statistics {

// Histogram2D::Histogram2D(int & nx_, int & ny_, int & nz_) : nx(nx_), ny(ny_), nz(nz_){
//     Resize(nx, ny, nz);
// };

Histogram2D::Histogram2D(std::string Name_,
                         std::vector<double> EdgesX_,
                         std::vector<double> EdgesY_) : Name(Name_), EdgesX(EdgesX_), EdgesY(EdgesY_) {
    nx = EdgesX.size() - 1;
    ny = EdgesY.size() - 1;

    Resize(nx, ny);
    InitializeIndexMap();
}

Histogram2D::Histogram2D(std::string Name_,
                         std::vector<double> EdgesX_,
                         std::vector<double> EdgesY_,
                         std::vector<double> EdgesZ_) : Name(Name_), EdgesX(EdgesX_), EdgesY(EdgesY_), EdgesZ(EdgesZ_) {
    nx = EdgesX.size() - 1;
    ny = EdgesY.size() - 1;
    thirdaxis = true;
    nz = 1;
    Resize(nx, ny);
    InitializeIndexMap();
}

void Histogram2D::Resize(int& nx_, int& ny_) {
    Contents.resize(nx_, Vector1D(ny_));
}

std::string& Histogram2D::GetName() {
    return Name;
}

void Histogram2D::AddEvent() {
    // std::cout << "#" << Contents[10][0][0][211].Total << std::endl;
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            Contents[ix][iy].AddEvent();
            // entry.second.Total += entry.second.TotalCurrent;
            // entry.second.TotalSQR += entry.second.TotalCurrent * entry.second.TotalCurrent;
            // entry.second.TotalCurrent = 0;
        }
    }
    // std::cout << "!" << Contents[10][0][0][211].Total << std::endl;
}

void Histogram2D::AddEventAverage() {
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            Contents[ix][iy].AddEventSpecial();
        }
    }
}

void Histogram2D::Add(double& valx, double& valy, double valcontent) {
    // std::cout << valx << " " << valy << " " << valcontent << std::endl;
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];

        Contents[ix][iy].Add(valcontent);
    }
}

void Histogram2D::AddCurrent(double& valx, double& valy, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];

        Contents[ix][iy].AddCurrent(valcontent);
    }
}

void Histogram2D::Add(double& valx, double& valy, double& valz, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max && valz >= z_min && valz < z_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];

        Contents[ix][iy].Add(valcontent);
    }
}

void Histogram2D::AddCurrent(double& valx, double& valy, double& valz, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max && valz >= z_min && valz < z_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];

        Contents[ix][iy].AddCurrent(valcontent);
    }
}

void Histogram2D::InitializeIndexMap() {
    x_max = EdgesX.back();
    x_min = EdgesX.front();
    y_max = EdgesY.back();
    y_min = EdgesY.front();
    if (thirdaxis) {
        z_max = EdgesZ.back();
        z_min = EdgesZ.front();
    }

    std::vector<double> xwidths(nx);
    std::vector<double> ywidths(ny);

    for (int ix = 0; ix < nx; ++ix) {
        xwidths[ix] = EdgesX[ix + 1] - EdgesX[ix];
        // std::cout << xwidths[ix] << std::endl;
    }
    for (int iy = 0; iy < ny; ++iy) {
        ywidths[iy] = EdgesY[iy + 1] - EdgesY[iy];
    }

    double x_smallest_width = xwidths[0];
    double y_smallest_width = ywidths[0];

    double x_temp_width;
    double y_temp_width;

    for (int ix = 0; ix < nx; ++ix) {
        for (int jx = ix + 1; jx < nx; ++jx) {
            x_temp_width = Utilities::igcd(xwidths[ix], xwidths[jx], 0.001);
            if (x_temp_width < x_smallest_width) {
                x_smallest_width = x_temp_width;
            }
        }
    }
    for (int iy = 0; iy < ny; ++iy) {
        for (int jy = iy + 1; jy < ny; ++jy) {
            y_temp_width = Utilities::igcd(ywidths[iy], ywidths[jy], 0.001);
            if (y_temp_width < y_smallest_width) {
                y_smallest_width = y_temp_width;
            }
        }
    }

    x_width = x_smallest_width;
    y_width = y_smallest_width;

    int temp_nx = static_cast<int>((x_max - x_min) / x_width);
    int temp_ny = static_cast<int>((y_max - y_min) / y_width);

    // std::cout << x_max << " " << x_min << " " << x_width << " " << temp_nx << std::endl;

    double x;
    double y;

    for (int ix = 0; ix < temp_nx; ++ix) {
        x = (x_min + ix * x_width + x_width * 0.5);

        for (int jx = 0; jx < nx; ++jx) {
            if (x > EdgesX[jx] && x < EdgesX[jx + 1]) {
                IndexMapX[ix] = jx;
            }
        }
    }
    for (int iy = 0; iy < temp_ny; ++iy) {
        y = (y_min + iy * y_width + y_width * 0.5);

        for (int jy = 0; jy < ny; ++jy) {
            if (y > EdgesY[jy] && y < EdgesY[jy + 1]) {
                IndexMapY[iy] = jy;
            }
        }
    }

    xwidths.clear();
    ywidths.clear();
}

void Histogram2D::PrintEdges(std::ostream& output) {
    output << "nbins(x) = " << nx << "\n";
    output << "edges(x) = ";
    for (int ix = 0; ix <= nx; ++ix) {
        output << EdgesX[ix] << " ";
    }
    output << "\n";
    output << "nbins(y) = " << ny << "\n";
    output << "edges(y) = ";
    for (int iy = 0; iy <= ny; ++iy) {
        output << EdgesY[iy] << " ";
    }
    output << "\n";
    if (thirdaxis) {
        output << "nbins(z) = " << nz << "\n";
        output << "edges(z) = ";
        for (int iz = 0; iz <= nz; ++iz) {
            output << EdgesZ[iz] << " ";
        }
        output << "\n";
    }
}

void Histogram2D::PrintCount(std::ostream& output) {
    // std::cout << nx << " " << ny << " " << nz << std::endl;
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            output << std::setw(13) << std::right << Contents[ix][iy].EntryCount << " ";
            // std::cout << Contents[ix][iy][iz].EntryCount << std::endl;
        }
        output << "\n";
    }
}
void Histogram2D::PrintTotalSQR(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            output << std::setw(13) << std::right << Contents[ix][iy].TotalSQR << " ";
        }
        output << "\n";
    }
}

void Histogram2D::PrintTotal(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            output << std::setw(13) << std::right << Contents[ix][iy].Total << " ";
        }
        output << "\n";
    }
}

StatisticsContainer& Histogram2D::operator()(int& ix, int& iy) {
    return Contents[ix][iy];
}

Vector1D& Histogram2D::operator()(int& ix) {
    return Contents[ix];
}

StatisticsContainer& Histogram2D::operator()(double& valx, double& valy) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    int iy = IndexMapY[static_cast<int>((valy - y_min) / (y_width))];

    return Contents[ix][iy];
}
Vector1D& Histogram2D::operator()(double& valx) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];

    return Contents[ix];
}

void Histogram2D::operator+=(Histogram2D const& obj) {
    if (nx == obj.nx && ny == obj.ny) {
        for (int ix = 0; ix < nx; ++ix) {
            for (int iy = 0; iy < ny; ++iy) {
                Contents[ix][iy] += obj.Contents[ix][iy];
            }
        }
    } else {
        printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
        printf("%s\n", "Cannot add two HistogramMaps of different sizes!");
    }
}

void Histogram2D::ReadEdges(std::string filename) {
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

    std::getline(file, line);
    iss = std::istringstream(line);

    iss >> dummy1 >> dummy2 >> ny;

    std::getline(file, line);
    iss = std::istringstream(line);

    iss >> dummy1 >> dummy2;

    while (iss >> edge) {
        EdgesY.push_back(edge);
    }

    std::getline(file, line);
    iss = std::istringstream(line);

    file.close();
    Resize(nx, ny);
    InitializeIndexMap();
}
void Histogram2D::ReadTotalSQR(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    file.open(filename, std::ios::in);
    for (int ix = 0; ix < nx; ++ix) {
        std::getline(file, line);

        iss = std::istringstream(line);
        for (int iy = 0; iy < ny; ++iy) {
            iss >> Contents[ix][iy].TotalSQR;
        }
    }
    file.close();
}
void Histogram2D::ReadTotal(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    file.open(filename, std::ios::in);
    for (int ix = 0; ix < nx; ++ix) {
        std::getline(file, line);

        iss = std::istringstream(line);
        for (int iy = 0; iy < ny; ++iy) {
            iss >> Contents[ix][iy].Total;
        }
    }
    file.close();
}
void Histogram2D::ReadCount(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    file.open(filename, std::ios::in);
    for (int ix = 0; ix < nx; ++ix) {
        std::getline(file, line);

        iss = std::istringstream(line);
        for (int iy = 0; iy < ny; ++iy) {
            iss >> Contents[ix][iy].EntryCount;
        }
    }
    file.close();
}

}  // namespace Statistics
// }
