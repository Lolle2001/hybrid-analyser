// Copyright (C) 2024 Lieuwe Huisman
#include "HistogramMap2D.hpp"

// namespace AMPT {
namespace Statistics {

// HistogramMap3D::HistogramMap3D(int& nx_, int& ny_, int& nz_) : nx(nx_), ny(ny_), nz(nz_) {
//     Resize(nx, ny, nz);
// };

HistogramMap2D::HistogramMap2D(
    std::string Name_,
    std::vector<double> EdgesX_,
    std::vector<double> EdgesY_) : Name(Name_), EdgesX(EdgesX_), EdgesY(EdgesY_) {
    nx = EdgesX.size() - 1;
    ny = EdgesY.size() - 1;

    Resize(nx, ny);
    InitializeIndexMap();
}

void HistogramMap2D::Resize(size_t& nx_, size_t& ny_) {
    Contents.resize(nx_, Vector1DMap(ny_));
}

std::string& HistogramMap2D::GetName() {
    return Name;
}

void HistogramMap2D::AddEvent() {
    // std::cout << "#" << Contents[10][0][0][211].Total << std::endl;
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            for (auto& entry : Contents[ix][iy]) {
                entry.second.AddEvent();
                // entry.second.Total += entry.second.TotalCurrent;
                // entry.second.TotalSQR += entry.second.TotalCurrent * entry.second.TotalCurrent;
                // entry.second.TotalCurrent = 0;
            }
        }
    }
    // std::cout << "!" << Contents[10][0][0][211].Total << std::endl;
}

void HistogramMap2D::AddEventAverage() {
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            for (auto& entry : Contents[ix][iy]) {
                entry.second.AddEventSpecial();
            }
        }
    }
}

void HistogramMap2D::Add(double& valx, double& valy, int& key, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];

        Contents[ix][iy][key].Add(valcontent);
    }
}

void HistogramMap2D::AddCurrent(double& valx, double& valy, int& key, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];

        Contents[ix][iy][key].AddCurrent(valcontent);
    }
}

void HistogramMap2D::InitializeIndexMap() {
    x_max = EdgesX.back();
    x_min = EdgesX.front();
    y_max = EdgesY.back();
    y_min = EdgesY.front();

    std::vector<double> xwidths(nx);
    std::vector<double> ywidths(ny);

    for (index_t ix = 0; ix < nx; ++ix) {
        xwidths[ix] = EdgesX[ix + 1] - EdgesX[ix];
        // std::cout << xwidths[ix] << std::endl;
    }
    for (index_t iy = 0; iy < ny; ++iy) {
        ywidths[iy] = EdgesY[iy + 1] - EdgesY[iy];
    }

    double x_smallest_width = xwidths[0];
    double y_smallest_width = ywidths[0];

    double x_temp_width;
    double y_temp_width;

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

    x_width = x_smallest_width;
    y_width = y_smallest_width;

    size_t temp_nx = static_cast<size_t>((x_max - x_min) / x_width);
    size_t temp_ny = static_cast<size_t>((y_max - y_min) / y_width);

    // std::cout << x_max << " " << x_min << " " << x_width << " " << temp_nx << std::endl;

    double x;
    double y;

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

    xwidths.clear();
    ywidths.clear();
}

void HistogramMap2D::Convert() {
    for (index_t ix = 0; ix < nx; ++ix) {
        // centrality
        for (index_t iy = 0; iy < ny; ++iy) {
            // momentum

            // rapidity
            for (const auto& entry : Contents[ix][iy]) {
                // std::cout << entry.second.Total << std::endl;
                if (ContentsConverted.count(entry.first) == 0) {
                    ContentsConverted[entry.first].resize(nx, std::vector<StatisticsContainer>(ny));
                    ContentsConverted[entry.first][ix][iy] = entry.second;
                } else {
                    ContentsConverted[entry.first][ix][iy] += entry.second;
                }
            }
        }
    }
}

void HistogramMap2D::PrintEdges(std::ostream& output) {
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
}

void HistogramMap2D::PrintCount(std::ostream& output) {
    output << "# " << ContentsConverted.size() << "\n";
    for (const auto& entry : ContentsConverted) {
        output << "# " << entry.first << "\n";
        for (index_t ix = 0; ix < nx; ++ix) {
            for (index_t iy = 0; iy < ny; ++iy) {
                output << std::setw(13) << std::right << entry.second[ix][iy].EntryCount << " ";
            }
            output << "\n";
        }
    }
}
void HistogramMap2D::PrintTotalSQR(std::ostream& output) {
    output << "# " << ContentsConverted.size() << "\n";
    for (const auto& entry : ContentsConverted) {
        output << "# " << entry.first << "\n";
        for (index_t ix = 0; ix < nx; ++ix) {
            for (index_t iy = 0; iy < ny; ++iy) {
                output << std::setw(13) << std::right << entry.second[ix][iy].TotalSQR << " ";
            }
            output << "\n";
        }
    }
}
void HistogramMap2D::PrintTotal(std::ostream& output) {
    output << "# " << ContentsConverted.size() << "\n";
    for (const auto& entry : ContentsConverted) {
        output << "# " << entry.first << "\n";
        for (index_t ix = 0; ix < nx; ++ix) {
            for (index_t iy = 0; iy < ny; ++iy) {
                output << std::setw(13) << std::right << entry.second[ix][iy].Total << " ";
            }
            output << "\n";
        }
    }
}

void HistogramMap2D::ReadEdges(std::string filename) {
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

    file.close();
    Resize(nx, ny);
    InitializeIndexMap();
}

void HistogramMap2D::ReadTotalSQR(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    std::string dummy1;
    std::string dummy2;
    size_t nids;
    int pid;
    file.open(filename, std::ios::in);
    std::getline(file, line);
    iss = std::istringstream(line);
    iss >> dummy1 >> nids;
    for (index_t ip = 0; ip < nids; ++ip) {
        std::getline(file, line);
        iss = std::istringstream(line);
        iss >> dummy1 >> pid;
        for (index_t ix = 0; ix < nx; ++ix) {
            std::getline(file, line);
            iss = std::istringstream(line);
            for (index_t iy = 0; iy < ny; ++iy) {
                iss >> Contents[ix][iy][pid].TotalSQR;
            }
        }
    }
    file.close();
}

void HistogramMap2D::ReadTotal(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    std::string dummy1;
    std::string dummy2;
    size_t nids;
    int pid;
    file.open(filename, std::ios::in);
    std::getline(file, line);
    iss = std::istringstream(line);
    iss >> dummy1 >> nids;
    for (index_t ip = 0; ip < nids; ++ip) {
        std::getline(file, line);
        iss = std::istringstream(line);
        iss >> dummy1 >> pid;
        for (index_t ix = 0; ix < nx; ++ix) {
            std::getline(file, line);
            iss = std::istringstream(line);
            for (index_t iy = 0; iy < ny; ++iy) {
                iss >> Contents[ix][iy][pid].Total;
            }
        }
    }
    file.close();
}

void HistogramMap2D::ReadCount(std::string filename) {
    std::ifstream file;
    std::string line;
    std::istringstream iss;

    std::string dummy1;
    std::string dummy2;
    size_t nids;
    int pid;
    file.open(filename, std::ios::in);
    std::getline(file, line);
    iss = std::istringstream(line);
    iss >> dummy1 >> nids;
    for (index_t ip = 0; ip < nids; ++ip) {
        std::getline(file, line);
        iss = std::istringstream(line);
        iss >> dummy1 >> pid;
        for (index_t ix = 0; ix < nx; ++ix) {
            std::getline(file, line);
            iss = std::istringstream(line);
            for (index_t iy = 0; iy < ny; ++iy) {
                iss >> Contents[ix][iy][pid].EntryCount;
            }
        }
    }
    file.close();
}

StatisticsContainer& HistogramMap2D::operator()(int& ix, int& iy, int& key) {
    return Contents[ix][iy][key];
}

Vector0DMap& HistogramMap2D::operator()(int& ix, int& iy) {
    return Contents[ix][iy];
}
Vector1DMap& HistogramMap2D::operator()(int& ix) {
    return Contents[ix];
}

StatisticsContainer& HistogramMap2D::operator()(double& valx, double& valy, int& key) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    int iy = IndexMapY[static_cast<int>((valy - y_min) / (y_width))];

    return Contents[ix][iy][key];
}

Vector0DMap& HistogramMap2D::operator()(double& valx, double& valy) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    int iy = IndexMapY[static_cast<int>((valy - y_min) / (y_width))];

    return Contents[ix][iy];
}
Vector1DMap& HistogramMap2D::operator()(double& valx) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];

    return Contents[ix];
}

void HistogramMap2D::operator+=(HistogramMap2D const& obj) {
    if (nx == obj.nx && ny == obj.ny) {
        for (index_t ix = 0; ix < nx; ++ix) {
            for (index_t iy = 0; iy < ny; ++iy) {
                for (auto entry : obj.Contents[ix][iy]) {
                    Contents[ix][iy][entry.first] += entry.second;
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
