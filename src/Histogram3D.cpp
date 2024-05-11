#include "Histogram3D.hpp"

// namespace AMPT {
namespace Statistics {

// Histogram3D::Histogram3D(int & nx_, int & ny_, int & nz_) : nx(nx_), ny(ny_), nz(nz_){
//     Resize(nx, ny, nz);
// };

Histogram3D::Histogram3D(
    std::string Name_,
    std::vector<double> EdgesX_,
    std::vector<double> EdgesY_,
    std::vector<double> EdgesZ_) : Name(Name_), EdgesX(EdgesX_), EdgesY(EdgesY_), EdgesZ(EdgesZ_) {
    nx = EdgesX.size() - 1;
    ny = EdgesY.size() - 1;
    nz = EdgesZ.size() - 1;
    Resize(nx, ny, nz);
    InitializeIndexMap();
}

std::string& Histogram3D::GetName() {
    return Name;
}

void Histogram3D::Resize(int& nx_, int& ny_, int& nz_) {
    Contents.resize(nx_ * ny_ * nz_);
}

void Histogram3D::AddEvent() {
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            for (int iz = 0; iz < nz; ++iz) {
                Contents[GetIndex(ix, iy, iz)].AddEvent();
            }
        }
    }
}

void Histogram3D::AddEventAverage() {
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            for (int iz = 0; iz < nz; ++iz) {
                Contents[GetIndex(ix, iy, iz)].AddEventSpecial();
            }
        }
    }
}

void Histogram3D::AddCurrent(double& valx, double& valy, double& valz, double valcontent) {
    if (valx > x_min && valx <= x_max && valy > y_min && valy <= y_max && valz > z_min && valz <= z_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];
        int iz = IndexMapZ[(int)((valz - z_min) / (z_width))];
        Contents[GetIndex(ix, iy, iz)].AddCurrent(valcontent);
    }
}

void Histogram3D::Add(double& valx, double& valy, double& valz, double valcontent) {
    if (valx > x_min && valx <= x_max && valy > y_min && valy <= y_max && valz > z_min && valz <= z_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];
        int iz = IndexMapZ[(int)((valz - z_min) / (z_width))];
        Contents[GetIndex(ix, iy, iz)].Add(valcontent);
    }
}

void Histogram3D::InitializeIndexMap() {
    if (EdgesX[1] - EdgesX[0] > 0) {
        x_max = EdgesX.back();
        x_min = EdgesX.front();
    } else {
        x_max = EdgesX.front();
        x_min = EdgesX.back();
    }

    y_max = EdgesY.back();
    y_min = EdgesY.front();
    z_max = EdgesZ.back();
    z_min = EdgesZ.front();

    x_width = Utilities::Statistics::CalculateCommonWidth(nx, EdgesX);
    Utilities::Statistics::FillIndexMap(nx, x_min, x_max, x_width, EdgesX, IndexMapX);
    y_width = Utilities::Statistics::CalculateCommonWidth(ny, EdgesY);
    Utilities::Statistics::FillIndexMap(ny, y_min, y_max, y_width, EdgesY, IndexMapY);
    z_width = Utilities::Statistics::CalculateCommonWidth(ny, EdgesZ);
    Utilities::Statistics::FillIndexMap(ny, z_min, z_max, z_width, EdgesZ, IndexMapZ);
}

void Histogram3D::ReverseEdges() {
    for (auto& entry : IndexMapX) {
        entry.second = nx - 1 - entry.second;
    }
    for (auto& entry : IndexMapY) {
        entry.second = ny - 1 - entry.second;
    }
    for (auto& entry : IndexMapZ) {
        entry.second = nz - 1 - entry.second;
    }
}

void Histogram3D::PrintEdges(std::ostream& output) {
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
    output << "nbins(z) = " << nz << "\n";
    output << "edges(z) = ";
    for (int iz = 0; iz <= nz; ++iz) {
        output << EdgesZ[iz] << " ";
    }
    output << "\n";
}

void Histogram3D::PrintCount(std::ostream& output) {
    // std::cout << nx << " " << ny << " " << nz << std::endl;
    for (int ix = 0; ix < nx; ++ix) {
        output << "# " << ix << "\n";
        for (int iy = 0; iy < ny; ++iy) {
            for (int iz = 0; iz < nz; ++iz) {
                output << Contents[GetIndex(ix, iy, iz)].EntryCount << " ";
                // std::cout << Contents[GetIndex(ix, iy, iz)].EntryCount << std::endl;
            }
            output << "\n";
        }
    }
}
void Histogram3D::PrintTotalSQR(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        output << "# " << ix << "\n";
        for (int iy = 0; iy < ny; ++iy) {
            for (int iz = 0; iz < nz; ++iz) {
                output << Contents[GetIndex(ix, iy, iz)].TotalSQR << " ";
            }
            output << "\n";
        }
    }
}
void Histogram3D::PrintTotal(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        output << "# " << ix << "\n";
        for (int iy = 0; iy < ny; ++iy) {
            for (int iz = 0; iz < nz; ++iz) {
                output << Contents[GetIndex(ix, iy, iz)].Total << " ";
            }
            output << "\n";
        }
    }
}

void Histogram3D::PrintVariance(std::ostream& output) {
    for (int ix = 0; ix < nx; ++ix) {
        output << "# " << ix << "\n";
        for (int iy = 0; iy < ny; ++iy) {
            for (int iz = 0; iz < nz; ++iz) {
                output << Contents[GetIndex(ix, iy, iz)].Variance << " ";
            }
            output << "\n";
        }
    }
}

StatisticsContainer& Histogram3D::operator()(int& ix, int& iy, int& iz) {
    return Contents[GetIndex(ix, iy, iz)];
}

// Vector1D& Histogram3D::operator()(int& ix, int& iy) {
//     return Contents[ix][iy];
// }
// Vector2D& Histogram3D::operator()(int& ix) {
//     return Contents[ix];
// }

StatisticsContainer& Histogram3D::operator()(double& valx, double& valy, double& valz) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    int iy = IndexMapY[static_cast<int>((valy - y_min) / (y_width))];
    int iz = IndexMapZ[static_cast<int>((valz - z_min) / (z_width))];
    return Contents[GetIndex(ix, iy, iz)];
}
// Vector1D& Histogram3D::operator()(double& valx, double& valy) {
//     int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
//     int iy = IndexMapY[static_cast<int>((valy - y_min) / (y_width))];
//     return Contents[ix][iy];
// }
// Vector2D& Histogram3D::operator()(double& valx) {
//     int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
//     return Contents[ix];
// }

void Histogram3D::operator+=(Histogram3D const& obj) {
    if (nx == obj.nx && ny == obj.ny && nz == obj.nz) {
        for (int ix = 0; ix < nx; ++ix) {
            for (int iy = 0; iy < ny; ++iy) {
                for (int iz = 0; iz < nz; ++iz) {
                    size_t index = GetIndex(ix, iy, iz);
                    Contents[index] += obj.Contents[index];
                }
            }
        }
    } else {
        printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
        printf("%s\n", "Cannot add two HistogramMaps of different sizes!");
    }
}

void Histogram3D::ReadEdges(std::string filename) {
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

    iss >> dummy1 >> dummy2 >> nz;

    std::getline(file, line);
    iss = std::istringstream(line);

    iss >> dummy1 >> dummy2;

    while (iss >> edge) {
        EdgesZ.push_back(edge);
    }

    file.close();
    Resize(nx, ny, nz);
    InitializeIndexMap();
}
void Histogram3D::ReadTotalSQR(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    file.open(filename, std::ios::in);
    for (int ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        for (int iy = 0; iy < ny; ++iy) {
            std::getline(file, line);
            iss = std::istringstream(line);
            for (int iz = 0; iz < nz; ++iz) {
                iss >> Contents[GetIndex(ix, iy, iz)].TotalSQR;
            }
        }
    }
    file.close();
}
void Histogram3D::ReadTotal(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    file.open(filename, std::ios::in);
    for (int ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        for (int iy = 0; iy < ny; ++iy) {
            std::getline(file, line);
            iss = std::istringstream(line);
            for (int iz = 0; iz < nz; ++iz) {
                iss >> Contents[GetIndex(ix, iy, iz)].Total;
            }
        }
    }
    file.close();
}
void Histogram3D::ReadCount(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    file.open(filename, std::ios::in);
    for (int ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        for (int iy = 0; iy < ny; ++iy) {
            std::getline(file, line);
            iss = std::istringstream(line);
            for (int iz = 0; iz < nz; ++iz) {
                iss >> Contents[GetIndex(ix, iy, iz)].EntryCount;
            }
        }
    }
    file.close();
}

}  // namespace Statistics
// }
