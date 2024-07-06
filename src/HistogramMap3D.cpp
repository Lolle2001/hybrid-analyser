// Copyright (C) 2024 Lieuwe Huisman
#include "HistogramMap3D.hpp"

// namespace AMPT {
namespace Statistics {

// HistogramMap3D::HistogramMap3D(int& nx_, int& ny_, int& nz_) : nx(nx_), ny(ny_), nz(nz_) {
//     Resize(nx, ny, nz);
// };

HistogramMap3D::HistogramMap3D(
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

void HistogramMap3D::Resize(size_t& nx_, size_t& ny_, size_t& nz_) {
    Contents.resize(nx_, Vector2DMap(ny_, Vector1DMap(nz_)));
}

std::string& HistogramMap3D::GetName() {
    return Name;
}

void HistogramMap3D::AddEvent() {
    // std::cout << "#" << Contents[10][0][0][211].Total << std::endl;
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            for (index_t iz = 0; iz < nz; ++iz) {
                for (auto& entry : Contents[ix][iy][iz]) {
                    entry.second.AddEvent();
                    // entry.second.Total += entry.second.TotalCurrent;
                    // entry.second.TotalSQR += entry.second.TotalCurrent * entry.second.TotalCurrent;
                    // entry.second.TotalCurrent = 0;
                }
            }
        }
    }
    // std::cout << "!" << Contents[10][0][0][211].Total << std::endl;
}

void HistogramMap3D::AddEventAverage() {
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            for (index_t iz = 0; iz < nz; ++iz) {
                for (auto& entry : Contents[ix][iy][iz]) {
                    entry.second.AddEventSpecial();
                }
            }
        }
    }
}

void HistogramMap3D::Add(double& valx, double& valy, double& valz, int& key, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max && valz >= z_min && valz < z_max) {
        index_t ix = IndexMapX[(index_t)((valx - x_min) / (x_width))];
        index_t iy = IndexMapY[(index_t)((valy - y_min) / (y_width))];
        index_t iz = IndexMapZ[(index_t)((valz - z_min) / (z_width))];
        Contents[ix][iy][iz][key].Add(valcontent);
    }
}

void HistogramMap3D::AddCurrent(double& valx, double& valy, double& valz, int& key, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max && valz >= z_min && valz < z_max) {
        index_t ix = IndexMapX[(index_t)((valx - x_min) / (x_width))];
        index_t iy = IndexMapY[(index_t)((valy - y_min) / (y_width))];
        index_t iz = IndexMapZ[(index_t)((valz - z_min) / (z_width))];
        Contents[ix][iy][iz][key].AddCurrent(valcontent);
    }
}

void HistogramMap3D::InitializeIndexMap() {
    x_max = EdgesX.back();
    x_min = EdgesX.front();
    y_max = EdgesY.back();
    y_min = EdgesY.front();
    z_max = EdgesZ.back();
    z_min = EdgesZ.front();

    std::vector<double> xwidths(nx);
    std::vector<double> ywidths(ny);
    std::vector<double> zwidths(nz);

    for (index_t ix = 0; ix < nx; ++ix) {
        xwidths[ix] = EdgesX[ix + 1] - EdgesX[ix];
        // std::cout << xwidths[ix] << std::endl;
    }
    for (index_t iy = 0; iy < ny; ++iy) {
        ywidths[iy] = EdgesY[iy + 1] - EdgesY[iy];
    }
    for (index_t iz = 0; iz < nz; ++iz) {
        zwidths[iz] = EdgesZ[iz + 1] - EdgesZ[iz];
    }

    double x_smallest_width = xwidths[0];
    double y_smallest_width = ywidths[0];
    double z_smallest_width = zwidths[0];

    double x_temp_width;
    double y_temp_width;
    double z_temp_width;

    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t jx = ix + 1; jx < nx; ++jx) {
            x_temp_width = Utilities::igcd(xwidths[ix], xwidths[jx], 0.001);
            if (x_temp_width < x_smallest_width) {
                x_smallest_width = x_temp_width;
            }
        }
    }
    for (index_t iy = 0; iy < ny; ++iy) {
        for (index_t jy = iy + 1; jy < ny; ++jy) {
            y_temp_width = Utilities::igcd(ywidths[iy], ywidths[jy], 0.001);
            if (y_temp_width < y_smallest_width) {
                y_smallest_width = y_temp_width;
            }
        }
    }
    for (index_t iz = 0; iz < nz; ++iz) {
        for (index_t jz = iz + 1; jz < nz; ++jz) {
            z_temp_width = Utilities::igcd(zwidths[iz], zwidths[jz], 0.001);
            if (z_temp_width < z_smallest_width) {
                z_smallest_width = z_temp_width;
            }
        }
    }

    x_width = x_smallest_width;
    y_width = y_smallest_width;
    z_width = z_smallest_width;

    size_t temp_nx = static_cast<size_t>((x_max - x_min) / x_width);
    size_t temp_ny = static_cast<size_t>((y_max - y_min) / y_width);
    size_t temp_nz = static_cast<size_t>((z_max - z_min) / z_width);

    // std::cout << x_max << " " << x_min << " " << x_width << " " << temp_nx << std::endl;

    double x;
    double y;
    double z;

    for (index_t ix = 0; ix < temp_nx; ++ix) {
        x = (x_min + ix * x_width + x_width * 0.5);

        for (index_t jx = 0; jx < nx; ++jx) {
            if (x > EdgesX[jx] && x < EdgesX[jx + 1]) {
                IndexMapX[ix] = jx;
            }
        }
    }
    for (index_t iy = 0; iy < temp_ny; ++iy) {
        y = (y_min + iy * y_width + y_width * 0.5);

        for (index_t jy = 0; jy < ny; ++jy) {
            if (y > EdgesY[jy] && y < EdgesY[jy + 1]) {
                IndexMapY[iy] = jy;
            }
        }
    }
    for (index_t iz = 0; iz < temp_nz; ++iz) {
        z = (z_min + iz * z_width + z_width * 0.5);

        for (index_t jz = 0; jz < nz; ++jz) {
            if (z > EdgesZ[jz] && z < EdgesZ[jz + 1]) {
                IndexMapZ[iz] = jz;
            }
        }
    }

    xwidths.clear();
    ywidths.clear();
    zwidths.clear();
}

void HistogramMap3D::Convert() {
    ContentsConverted.resize(nx);
    for (index_t ix = 0; ix < nx; ++ix) {
        // centrality
        for (index_t iy = 0; iy < ny; ++iy) {
            // momentum
            for (index_t iz = 0; iz < nz; ++iz) {
                // rapidity
                for (const auto& entry : Contents[ix][iy][iz]) {
                    // std::cout << entry.second.Total << std::endl;
                    if (ContentsConverted[ix].count(entry.first) == 0) {
                        ContentsConverted[ix][entry.first].resize(ny, std::vector<StatisticsContainer>(nz));
                        ContentsConverted[ix][entry.first][iy][iz] = entry.second;
                    } else {
                        ContentsConverted[ix][entry.first][iy][iz] += entry.second;
                    }
                }
            }
        }
    }
}

void HistogramMap3D::PrintEdges(std::ostream& output) {
    output << "nbins(x) = " << nx << "\n";
    output << "edges(x) = ";
    for (index_t ix = 0; ix <= nx; ++ix) {
        output << EdgesX[ix] << " ";
    }
    output << "\n";
    output << "nbins(y) = " << ny << "\n";
    output << "edges(y) = ";
    for (index_t iy = 0; iy <= ny; ++iy) {
        output << EdgesY[iy] << " ";
    }
    output << "\n";
    output << "nbins(z) = " << nz << "\n";
    output << "edges(z) = ";
    for (index_t iz = 0; iz <= nz; ++iz) {
        output << EdgesZ[iz] << " ";
    }
    output << "\n";
}

void HistogramMap3D::PrintCount(std::ostream& output) {
    for (index_t ix = 0; ix < nx; ++ix) {
        // centrality
        output << "# " << ix << " " << ContentsConverted[ix].size() << "\n";
        for (const auto& entry : ContentsConverted[ix]) {
            // pid
            std::stringstream line;
            line << std::setw(7) << std::right << entry.first << " ";
            for (index_t iy = 0; iy < ny; ++iy) {
                // momentum
                for (index_t iz = 0; iz < nz; ++iz) {
                    // rapidity
                    line << std::setw(15) << std::right << entry.second[iy][iz].EntryCount << " ";
                }
            }
            output << line.str() << "\n";
        }
    }
}
void HistogramMap3D::PrintTotalSQR(std::ostream& output) {
    for (index_t ix = 0; ix < nx; ++ix) {
        // centrality
        output << "# " << ix << " " << ContentsConverted[ix].size() << "\n";
        for (const auto& entry : ContentsConverted[ix]) {
            // pid
            std::stringstream line;
            line << std::setw(7) << std::right << entry.first << " ";
            for (index_t iy = 0; iy < ny; ++iy) {
                // momentum
                for (index_t iz = 0; iz < nz; ++iz) {
                    // rapidity
                    line << std::setw(15) << std::right << entry.second[iy][iz].TotalSQR << " ";
                }
            }
            output << line.str() << "\n";
        }
    }
}
void HistogramMap3D::PrintTotal(std::ostream& output) {
    for (index_t ix = 0; ix < nx; ++ix) {
        // centrality
        output << "# " << ix << " " << ContentsConverted[ix].size() << "\n";
        for (const auto& entry : ContentsConverted[ix]) {
            // pid
            std::stringstream line;
            line << std::setw(7) << std::right << entry.first << " ";
            for (index_t iy = 0; iy < ny; ++iy) {
                // momentum
                for (index_t iz = 0; iz < nz; ++iz) {
                    // rapidity
                    line << std::setw(15) << std::right << entry.second[iy][iz].Total << " ";
                }
            }
            output << line.str() << "\n";
        }
    }
}

void HistogramMap3D::ReadEdges(std::string filename) {
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

void HistogramMap3D::ReadTotalSQR(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    std::string dummy1;
    std::string dummy2;
    size_t nids;
    int pid;
    file.open(filename, std::ios::in);

    for (index_t ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        iss = std::istringstream(line);

        iss >> dummy1 >> dummy2 >> nids;

        for (index_t ip = 0; ip < nids; ++ip) {
            std::getline(file, line);
            iss = std::istringstream(line);
            iss >> pid;

            for (index_t iy = 0; iy < ny; ++iy) {
                for (index_t iz = 0; iz < nz; ++iz) {
                    iss >> Contents[ix][iy][iz][pid].TotalSQR;
                }
            }
        }
    }
    file.close();
}

void HistogramMap3D::ReadTotal(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    std::string dummy1;
    std::string dummy2;
    size_t nids;
    int pid;
    file.open(filename, std::ios::in);

    for (index_t ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        iss = std::istringstream(line);

        iss >> dummy1 >> dummy2 >> nids;

        for (index_t ip = 0; ip < nids; ++ip) {
            std::getline(file, line);
            iss = std::istringstream(line);
            iss >> pid;

            for (index_t iy = 0; iy < ny; ++iy) {
                for (index_t iz = 0; iz < nz; ++iz) {
                    iss >> Contents[ix][iy][iz][pid].Total;
                }
            }
        }
    }
    file.close();
}

void HistogramMap3D::ReadCount(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    std::string dummy1;
    std::string dummy2;
    size_t nids;
    int pid;
    file.open(filename, std::ios::in);

    for (index_t ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        iss = std::istringstream(line);

        iss >> dummy1 >> dummy2 >> nids;

        for (index_t ip = 0; ip < nids; ++ip) {
            std::getline(file, line);
            iss = std::istringstream(line);
            iss >> pid;

            for (index_t iy = 0; iy < ny; ++iy) {
                for (index_t iz = 0; iz < nz; ++iz) {
                    iss >> Contents[ix][iy][iz][pid].EntryCount;
                }
            }
        }
    }
    file.close();
}

StatisticsContainer& HistogramMap3D::operator()(index_t& ix, index_t& iy, index_t& iz, index_t& key) {
    return Contents[ix][iy][iz][key];
}

Vector0DMap& HistogramMap3D::operator()(index_t& ix, index_t& iy, index_t& iz) {
    return Contents[ix][iy][iz];
}
Vector1DMap& HistogramMap3D::operator()(index_t& ix, index_t& iy) {
    return Contents[ix][iy];
}
Vector2DMap& HistogramMap3D::operator()(index_t& ix) {
    return Contents[ix];
}

StatisticsContainer& HistogramMap3D::operator()(double& valx, double& valy, double& valz, int& key) {
    index_t ix = IndexMapX[static_cast<index_t>((valx - x_min) / (x_width))];
    index_t iy = IndexMapY[static_cast<index_t>((valy - y_min) / (y_width))];
    index_t iz = IndexMapZ[static_cast<index_t>((valz - z_min) / (z_width))];

    return Contents[ix][iy][iz][key];
}

Vector0DMap& HistogramMap3D::operator()(double& valx, double& valy, double& valz) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    int iy = IndexMapY[static_cast<int>((valy - y_min) / (y_width))];
    int iz = IndexMapZ[static_cast<int>((valz - z_min) / (z_width))];
    return Contents[ix][iy][iz];
}
Vector1DMap& HistogramMap3D::operator()(double& valx, double& valy) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    int iy = IndexMapY[static_cast<int>((valy - y_min) / (y_width))];
    return Contents[ix][iy];
}
Vector2DMap& HistogramMap3D::operator()(double& valx) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    return Contents[ix];
}

void HistogramMap3D::operator+=(HistogramMap3D const& obj) {
    if (nx == obj.nx && ny == obj.ny && nz == obj.nz) {
        for (index_t ix = 0; ix < nx; ++ix) {
            for (index_t iy = 0; iy < ny; ++iy) {
                for (index_t iz = 0; iz < nz; ++iz) {
                    for (auto entry : obj.Contents[ix][iy][iz]) {
                        Contents[ix][iy][iz][entry.first] += entry.second;
                    }
                }
            }
        }
    } else {
        printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
        printf("%s\n", "Cannot add two HistogramMaps of different sizes!");
    }
}

}  // namespace Statistics
// }
