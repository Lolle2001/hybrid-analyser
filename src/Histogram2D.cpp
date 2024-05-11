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

void Histogram2D::Resize(int nx_, int ny_) {
    Contents.resize(nx_ * ny_);
}

std::string& Histogram2D::GetName() {
    return Name;
}

void Histogram2D::AddEvent() {
    // std::cout << "#" << Contents[10][0][0][211].Total << std::endl;
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            Contents[GetIndex(ix, iy)].AddEvent();
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
            Contents[GetIndex(ix, iy)].AddEventSpecial();
        }
    }
}

void Histogram2D::Add(double& valx, double& valy, double valcontent) {
    // std::cout << valx << " " << valy << " " << valcontent << std::endl;
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];

        Contents[GetIndex(ix, iy)].Add(valcontent);
    }
}

void Histogram2D::AddCurrent(double& valx, double& valy, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];

        Contents[GetIndex(ix, iy)].AddCurrent(valcontent);
    }
}

void Histogram2D::Add(double& valx, double& valy, double& valz, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max && valz >= z_min && valz < z_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];

        Contents[GetIndex(ix, iy)].Add(valcontent);
    }
}

void Histogram2D::AddCurrent(double& valx, double& valy, double& valz, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max && valz >= z_min && valz < z_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];

        Contents[GetIndex(ix, iy)].AddCurrent(valcontent);
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

    x_width = Utilities::Statistics::CalculateCommonWidth(nx, EdgesX);
    Utilities::Statistics::FillIndexMap(nx, x_min, x_max, x_width, EdgesX, IndexMapX);
    y_width = Utilities::Statistics::CalculateCommonWidth(ny, EdgesY);
    Utilities::Statistics::FillIndexMap(ny, y_min, y_max, y_width, EdgesY, IndexMapY);
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
            output << std::setw(13) << std::right << Contents[GetIndex(ix, iy)].EntryCount << " ";
            // std::cout << Contents[GetIndex(ix,iy)][iz].EntryCount << std::endl;
        }
        output << "\n";
    }
}
void Histogram2D::PrintTotalSQR(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            output << std::setw(13) << std::right << Contents[GetIndex(ix, iy)].TotalSQR << " ";
        }
        output << "\n";
    }
}

void Histogram2D::PrintTotal(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            output << std::setw(13) << std::right << Contents[GetIndex(ix, iy)].Total << " ";
        }
        output << "\n";
    }
}

StatisticsContainer& Histogram2D::operator()(int& ix, int& iy) {
    return Contents[GetIndex(ix, iy)];
}

// Vector1D& Histogram2D::operator()(int& ix) {
//     return Contents[ix];
// }

StatisticsContainer& Histogram2D::operator()(double& valx, double& valy) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    int iy = IndexMapY[static_cast<int>((valy - y_min) / (y_width))];

    return Contents[GetIndex(ix, iy)];
}
// Vector1D& Histogram2D::operator()(double& valx) {
//     int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];

//     return Contents[ix];
// }

void Histogram2D::operator+=(Histogram2D const& obj) {
    if (nx == obj.nx && ny == obj.ny) {
        for (int ix = 0; ix < nx; ++ix) {
            for (int iy = 0; iy < ny; ++iy) {
                size_t index = GetIndex(ix, iy);
                Contents[index] += obj.Contents[index];
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
            iss >> Contents[GetIndex(ix, iy)].TotalSQR;
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
            iss >> Contents[GetIndex(ix, iy)].Total;
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
            iss >> Contents[GetIndex(ix, iy)].EntryCount;
        }
    }
    file.close();
}

}  // namespace Statistics
// }
