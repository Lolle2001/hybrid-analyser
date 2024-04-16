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
    Contents.resize(nx_, Vector2D(ny_, Vector1D(nz_)));
}

void Histogram3D::AddEvent() {
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            for (int iz = 0; iz < nz; ++iz) {
                Contents[ix][iy][iz].AddEvent();
            }
        }
    }
}

void Histogram3D::AddEventAverage() {
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            for (int iz = 0; iz < nz; ++iz) {
                Contents[ix][iy][iz].AddEventSpecial();
            }
        }
    }
}

void Histogram3D::AddCurrent(double& valx, double& valy, double& valz, double valcontent) {
    if (valx > x_min && valx <= x_max && valy > y_min && valy <= y_max && valz > z_min && valz <= z_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];
        int iz = IndexMapZ[(int)((valz - z_min) / (z_width))];
        Contents[ix][iy][iz].AddCurrent(valcontent);
    }
}

void Histogram3D::Add(double& valx, double& valy, double& valz, double valcontent) {
    if (valx > x_min && valx <= x_max && valy > y_min && valy <= y_max && valz > z_min && valz <= z_max) {
        int ix = IndexMapX[(int)((valx - x_min) / (x_width))];
        int iy = IndexMapY[(int)((valy - y_min) / (y_width))];
        int iz = IndexMapZ[(int)((valz - z_min) / (z_width))];
        Contents[ix][iy][iz].Add(valcontent);
    }
}

// void Histogram3D::InitializeIndexMap() {
//     x_max = EdgesX.back();
//     x_min = EdgesX.front();
//     y_max = EdgesY.back();
//     y_min = EdgesY.front();
//     z_max = EdgesZ.back();
//     z_min = EdgesZ.front();

//     std::vector<double> xwidths(nx);
//     std::vector<double> ywidths(ny);
//     std::vector<double> zwidths(nz);

//     for (int ix = 0; ix < nx; ++ix) {
//         xwidths[ix] = EdgesX[ix + 1] - EdgesX[ix];
//         // std::cout << xwidths[ix] << std::endl;
//     }
//     for (int iy = 0; iy < ny; ++iy) {
//         ywidths[iy] = EdgesY[iy + 1] - EdgesY[iy];
//     }
//     for (int iz = 0; iz < nz; ++iz) {
//         zwidths[iz] = EdgesZ[iz + 1] - EdgesZ[iz];
//     }

//     double x_smallest_width = xwidths[0];
//     double y_smallest_width = ywidths[0];
//     double z_smallest_width = zwidths[0];

//     double x_temp_width;
//     double y_temp_width;
//     double z_temp_width;

//     for (int ix = 0; ix < nx; ++ix) {
//         for (int jx = ix + 1; jx < nx; ++jx) {
//             x_temp_width = Utilities::igcd(xwidths[ix], xwidths[jx], 0.001);
//             if (x_temp_width < x_smallest_width) {
//                 x_smallest_width = x_temp_width;
//             }
//         }
//     }
//     for (int iy = 0; iy < ny; ++iy) {
//         for (int jy = iy + 1; jy < ny; ++jy) {
//             y_temp_width = Utilities::igcd(ywidths[iy], ywidths[jy], 0.001);
//             if (y_temp_width < y_smallest_width) {
//                 y_smallest_width = y_temp_width;
//             }
//         }
//     }
//     for (int iz = 0; iz < nz; ++iz) {
//         for (int jz = iz + 1; jz < nz; ++jz) {
//             z_temp_width = Utilities::igcd(zwidths[iz], zwidths[jz], 0.001);
//             if (z_temp_width < z_smallest_width) {
//                 z_smallest_width = z_temp_width;
//             }
//         }
//     }

//     x_width = x_smallest_width;
//     y_width = y_smallest_width;
//     z_width = z_smallest_width;

//     int temp_nx = static_cast<int>((x_max - x_min) / x_width);
//     int temp_ny = static_cast<int>((y_max - y_min) / y_width);
//     int temp_nz = static_cast<int>((z_max - z_min) / z_width);

//     // std::cout << x_max << " " << x_min << " " << x_width << " " << temp_nx << std::endl;

//     double x;
//     double y;
//     double z;

//     for (int ix = 0; ix < temp_nx; ++ix) {
//         x = (x_min + ix * x_width + x_width * 0.5);

//         for (int jx = 0; jx < nx; ++jx) {
//             if (x > EdgesX[jx] && x < EdgesX[jx + 1]) {
//                 IndexMapX[ix] = jx;
//             }
//         }
//     }
//     for (int iy = 0; iy < temp_ny; ++iy) {
//         y = (y_min + iy * y_width + y_width * 0.5);

//         for (int jy = 0; jy < ny; ++jy) {
//             if (y > EdgesY[jy] && y < EdgesY[jy + 1]) {
//                 IndexMapY[iy] = jy;
//             }
//         }
//     }
//     for (int iz = 0; iz < temp_nz; ++iz) {
//         z = (z_min + iz * z_width + z_width * 0.5);

//         for (int jz = 0; jz < nz; ++jz) {
//             if (z > EdgesZ[jz] && z < EdgesZ[jz + 1]) {
//                 IndexMapZ[iz] = jz;
//             }
//         }
//     // }

//     // for (int ix = 0; ix < temp_nx; ++ix) {
//     //     x = (x_min + ix * x_width + x_width * 0.5);

//     //     for (int jx = 0; jx < nx; ++jx) {
//     //         if ((EdgesX[0] < EdgesX[1] && x > EdgesX[jx] && x < EdgesX[jx + 1]) ||
//     //             (EdgesX[0] > EdgesX[1] && x < EdgesX[jx] && x > EdgesX[jx + 1])) {
//     //             IndexMapX[ix] = jx;
//     //         }
//     //     }
//     // }
//     // for (int iy = 0; iy < temp_ny; ++iy) {
//     //     y = (y_min + iy * y_width + y_width * 0.5);

//     //     for (int jy = 0; jy < ny; ++jy) {
//     //         if ((EdgesY[0] < EdgesY[1] && y > EdgesY[jy] && y < EdgesY[jy + 1]) ||
//     //             (EdgesY[0] > EdgesY[1] && y < EdgesY[jy] && y > EdgesY[jy + 1])) {
//     //             IndexMapY[iy] = jy;
//     //         }
//     //     }
//     // }
//     // for (int iz = 0; iz < temp_nz; ++iz) {
//     //     z = (z_min + iz * z_width + z_width * 0.5);

//     //     for (int jz = 0; jz < nz; ++jz) {
//     //         if ((EdgesZ[0] < EdgesZ[1] && z > EdgesZ[jz] && z < EdgesZ[jz + 1]) ||
//     //             (EdgesZ[0] > EdgesZ[1] && z < EdgesZ[jz] && z > EdgesZ[jz + 1])) {
//     //             IndexMapZ[iz] = jz;
//     //         }
//     //     }
//     // }

//     xwidths.clear();
//     ywidths.clear();
//     zwidths.clear();
// }
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

    std::vector<double> xwidths(nx);
    std::vector<double> ywidths(ny);
    std::vector<double> zwidths(nz);

    for (int ix = 0; ix < nx; ++ix) {
        xwidths[ix] = std::abs(EdgesX[ix + 1] - EdgesX[ix]);
    }
    for (int iy = 0; iy < ny; ++iy) {
        ywidths[iy] = std::abs(EdgesY[iy + 1] - EdgesY[iy]);
    }
    for (int iz = 0; iz < nz; ++iz) {
        zwidths[iz] = std::abs(EdgesZ[iz + 1] - EdgesZ[iz]);
    }

    double x_smallest_width = xwidths[0];
    double y_smallest_width = ywidths[0];
    double z_smallest_width = zwidths[0];

    // Find the smallest width for each dimension
    for (int ix = 0; ix < nx; ++ix) {
        for (int jx = ix + 1; jx < nx; ++jx) {
            double x_temp_width = Utilities::igcd(xwidths[ix], xwidths[jx], 0.001);
            if (x_temp_width < x_smallest_width) {
                x_smallest_width = x_temp_width;
            }
        }
    }
    for (int iy = 0; iy < ny; ++iy) {
        for (int jy = iy + 1; jy < ny; ++jy) {
            double y_temp_width = Utilities::igcd(ywidths[iy], ywidths[jy], 0.001);
            if (y_temp_width < y_smallest_width) {
                y_smallest_width = y_temp_width;
            }
        }
    }
    for (int iz = 0; iz < nz; ++iz) {
        for (int jz = iz + 1; jz < nz; ++jz) {
            double z_temp_width = Utilities::igcd(zwidths[iz], zwidths[jz], 0.001);
            if (z_temp_width < z_smallest_width) {
                z_smallest_width = z_temp_width;
            }
        }
    }

    // Assign the smallest width to each dimension
    x_width = x_smallest_width;
    y_width = y_smallest_width;
    z_width = z_smallest_width;

    // Calculate the number of bins for each dimension
    int temp_nx = static_cast<int>((x_max - x_min) / x_width);
    int temp_ny = static_cast<int>((y_max - y_min) / y_width);
    int temp_nz = static_cast<int>((z_max - z_min) / z_width);

    // Assign index mappings for each dimension
    double x;
    double y;
    double z;

    for (int ix = 0; ix < temp_nx; ++ix) {
        x = (x_min + ix * x_width + x_width * 0.5);

        for (int jx = 0; jx < nx; ++jx) {
            if ((EdgesX[0] < EdgesX[1] && x > EdgesX[jx] && x < EdgesX[jx + 1]) ||
                (EdgesX[0] > EdgesX[1] && x < EdgesX[jx] && x > EdgesX[jx + 1])) {
                IndexMapX[ix] = jx;
            }
        }
    }
    for (int iy = 0; iy < temp_ny; ++iy) {
        y = (y_min + iy * y_width + y_width * 0.5);

        for (int jy = 0; jy < ny; ++jy) {
            if ((EdgesY[0] < EdgesY[1] && y > EdgesY[jy] && y < EdgesY[jy + 1]) ||
                (EdgesY[0] > EdgesY[1] && y < EdgesY[jy] && y > EdgesY[jy + 1])) {
                IndexMapY[iy] = jy;
            }
        }
    }
    for (int iz = 0; iz < temp_nz; ++iz) {
        z = (z_min + iz * z_width + z_width * 0.5);

        for (int jz = 0; jz < nz; ++jz) {
            if ((EdgesZ[0] < EdgesZ[1] && z > EdgesZ[jz] && z < EdgesZ[jz + 1]) ||
                (EdgesZ[0] > EdgesZ[1] && z < EdgesZ[jz] && z > EdgesZ[jz + 1])) {
                IndexMapZ[iz] = jz;
            }
        }
    }

    xwidths.clear();
    ywidths.clear();
    zwidths.clear();
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
                output << Contents[ix][iy][iz].EntryCount << " ";
                // std::cout << Contents[ix][iy][iz].EntryCount << std::endl;
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
                output << Contents[ix][iy][iz].TotalSQR << " ";
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
                output << Contents[ix][iy][iz].Total << " ";
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
                output << Contents[ix][iy][iz].Variance << " ";
            }
            output << "\n";
        }
    }
}

StatisticsContainer& Histogram3D::operator()(int& ix, int& iy, int& iz) {
    return Contents[ix][iy][iz];
}

Vector1D& Histogram3D::operator()(int& ix, int& iy) {
    return Contents[ix][iy];
}
Vector2D& Histogram3D::operator()(int& ix) {
    return Contents[ix];
}

StatisticsContainer& Histogram3D::operator()(double& valx, double& valy, double& valz) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    int iy = IndexMapY[static_cast<int>((valy - y_min) / (y_width))];
    int iz = IndexMapZ[static_cast<int>((valz - z_min) / (z_width))];
    return Contents[ix][iy][iz];
}
Vector1D& Histogram3D::operator()(double& valx, double& valy) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    int iy = IndexMapY[static_cast<int>((valy - y_min) / (y_width))];
    return Contents[ix][iy];
}
Vector2D& Histogram3D::operator()(double& valx) {
    int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];
    return Contents[ix];
}

void Histogram3D::operator+=(Histogram3D const& obj) {
    if (nx == obj.nx && ny == obj.ny && nz == obj.nz) {
        for (int ix = 0; ix < nx; ++ix) {
            for (int iy = 0; iy < ny; ++iy) {
                for (int iz = 0; iz < nz; ++iz) {
                    Contents[ix][iy][iz] += obj.Contents[ix][iy][iz];
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
                iss >> Contents[ix][iy][iz].TotalSQR;
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
                iss >> Contents[ix][iy][iz].Total;
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
                iss >> Contents[ix][iy][iz].EntryCount;
            }
        }
    }
    file.close();
}

}  // namespace Statistics
// }
