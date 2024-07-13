// Copyright (C) 2024 Lieuwe Huisman
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

void Histogram3D::Resize(size_t& nx_, size_t& ny_, size_t& nz_) {
    Contents.resize(nx_ * ny_ * nz_);
}

void Histogram3D::AddEvent() {
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            for (index_t iz = 0; iz < nz; ++iz) {
                Contents[GetIndex(ix, iy, iz)].AddEvent();
            }
        }
    }
}

void Histogram3D::AddEventAverage() {
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            for (index_t iz = 0; iz < nz; ++iz) {
                Contents[GetIndex(ix, iy, iz)].AddEventSpecial();
            }
        }
    }
}

void Histogram3D::AddCurrent(double& valx, double& valy, double& valz, double valcontent) {
    if (valx > x_min && valx <= x_max && valy > y_min && valy <= y_max && valz > z_min && valz <= z_max) {
        index_t ix = IndexMapX[(index_t)((valx - x_min) / (x_width))];
        index_t iy = IndexMapY[(index_t)((valy - y_min) / (y_width))];
        index_t iz = IndexMapZ[(index_t)((valz - z_min) / (z_width))];
        Contents[GetIndex(ix, iy, iz)].AddCurrent(valcontent);
    }
}

void Histogram3D::Add(double& valx, double& valy, double& valz, double valcontent) {
    if (valx > x_min && valx <= x_max && valy > y_min && valy <= y_max && valz > z_min && valz <= z_max) {
        index_t ix = IndexMapX[(index_t)((valx - x_min) / (x_width))];
        index_t iy = IndexMapY[(index_t)((valy - y_min) / (y_width))];
        index_t iz = IndexMapZ[(index_t)((valz - z_min) / (z_width))];
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

void Histogram3D::PrintAll(std::ostream& output) {
    nlohmann::json j;

    std::vector<std::vector<std::vector<double>>> average(nx, std::vector<std::vector<double>>(ny, std::vector<double>(nz, 0)));
    std::vector<std::vector<std::vector<double>>> averagesqr(nx, std::vector<std::vector<double>>(ny, std::vector<double>(nz, 0)));
    std::vector<std::vector<std::vector<double>>> total(nx, std::vector<std::vector<double>>(ny, std::vector<double>(nz, 0)));
    std::vector<std::vector<std::vector<double>>> totalsqr(nx, std::vector<std::vector<double>>(ny, std::vector<double>(nz, 0)));
    std::vector<std::vector<std::vector<double>>> error(nx, std::vector<std::vector<double>>(ny, std::vector<double>(nz, 0)));
    std::vector<std::vector<std::vector<size_t>>> count(nx, std::vector<std::vector<size_t>>(ny, std::vector<size_t>(nz, 0)));

    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            for (index_t iz = 0; iz < nz; ++iz) {
                index_t index = GetIndex(ix, iy, iz);
                average[ix][iy][iz] = Contents[index].Total / Contents[index].EntryCount;
                averagesqr[ix][iy][iz] = Contents[index].TotalSQR / Contents[index].EntryCount;
                total[ix][iy][iz] = Contents[index].Total;
                totalsqr[ix][iy][iz] = Contents[index].TotalSQR;
                error[ix][iy][iz] = std::sqrt(averagesqr[ix][iy][iz] - average[ix][iy][iz] * average[ix][iy][iz]);
                count[ix][iy][iz] = Contents[index].EntryCount;
            }
        }
    }
    std::vector<double> xmids(nx);
    std::vector<double> ymids(ny);
    std::vector<double> zmids(nz);
    std::vector<double> xwids(nx);
    std::vector<double> ywids(ny);
    std::vector<double> zwids(nz);
    std::vector<double> xerr(nx);
    std::vector<double> yerr(ny);
    std::vector<double> zerr(nz);

    for (index_t ix = 0; ix < nx; ++ix) {
        xmids[ix] = (EdgesX[ix + 1] + EdgesX[ix]) / 2;
        xwids[ix] = (EdgesX[ix + 1] - EdgesX[ix]);
        xerr[ix] = (EdgesX[ix + 1] - EdgesX[ix]) / 2;
    }
    for (index_t iy = 0; iy < ny; ++iy) {
        ymids[iy] = (EdgesY[iy + 1] + EdgesY[iy]) / 2;
        ywids[iy] = (EdgesY[iy + 1] - EdgesY[iy]);
        yerr[iy] = (EdgesY[iy + 1] - EdgesY[iy]) / 2;
    }
    for (index_t iz = 0; iz < nz; ++iz) {
        zmids[iz] = (EdgesZ[iz + 1] + EdgesZ[iz]) / 2;
        zwids[iz] = (EdgesZ[iz + 1] - EdgesZ[iz]);
        zerr[iz] = (EdgesZ[iz + 1] - EdgesZ[iz]) / 2;
    }

    j["name"] = Name;
    j["settings"]["nbins"]["x"] = nx;
    j["settings"]["edges"]["x"] = EdgesX;
    j["settings"]["wids"]["x"] = xwids;
    j["settings"]["mids"]["x"] = xmids;
    j["settings"]["errs"]["x"] = xerr;
    j["settings"]["names"]["x"] = "ph";

    j["settings"]["nbins"]["y"] = ny;
    j["settings"]["edges"]["y"] = EdgesY;
    j["settings"]["wids"]["y"] = ywids;
    j["settings"]["mids"]["y"] = ymids;
    j["settings"]["errs"]["y"] = yerr;
    j["settings"]["names"]["y"] = "ph";

    j["settings"]["nbins"]["z"] = nz;
    j["settings"]["edges"]["z"] = EdgesZ;
    j["settings"]["wids"]["z"] = zwids;
    j["settings"]["mids"]["z"] = zmids;
    j["settings"]["errs"]["z"] = zerr;
    j["settings"]["names"]["z"] = "ph";

    j["settings"]["dimension"] = 3;
    nlohmann::json javerage(average);
    nlohmann::json javeragesqr(averagesqr);
    nlohmann::json jerror(error);
    nlohmann::json jtotal(total);
    nlohmann::json jtotalsqr(totalsqr);
    nlohmann::json jcount(count);

    j["contents"]["average"] = javerage;
    j["contents"]["averagesqr"] = javeragesqr;
    j["contents"]["error"] = jerror;
    j["contents"]["total"] = jtotal;
    j["contents"]["totalsqr"] = jtotalsqr;
    j["contents"]["count"] = jcount;
    j["contents"]["name"] = Name;

    output << j.dump(4);
}

void Histogram3D::PrintEdges(std::ostream& output) {
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

void Histogram3D::PrintCount(std::ostream& output) {
    // std::cout << nx << " " << ny << " " << nz << std::endl;
    for (index_t ix = 0; ix < nx; ++ix) {
        output << "# " << ix << "\n";
        for (index_t iy = 0; iy < ny; ++iy) {
            for (index_t iz = 0; iz < nz; ++iz) {
                output << Contents[GetIndex(ix, iy, iz)].EntryCount << " ";
                // std::cout << Contents[GetIndex(ix, iy, iz)].EntryCount << std::endl;
            }
            output << "\n";
        }
    }
}
void Histogram3D::PrintTotalSQR(std::ostream& output) {
    for (index_t ix = 0; ix < nx; ++ix) {
        output << "# " << ix << "\n";
        for (index_t iy = 0; iy < ny; ++iy) {
            for (index_t iz = 0; iz < nz; ++iz) {
                output << Contents[GetIndex(ix, iy, iz)].TotalSQR << " ";
            }
            output << "\n";
        }
    }
}
void Histogram3D::PrintTotal(std::ostream& output) {
    for (index_t ix = 0; ix < nx; ++ix) {
        output << "# " << ix << "\n";
        for (index_t iy = 0; iy < ny; ++iy) {
            for (index_t iz = 0; iz < nz; ++iz) {
                output << Contents[GetIndex(ix, iy, iz)].Total << " ";
            }
            output << "\n";
        }
    }
}

void Histogram3D::PrintVariance(std::ostream& output) {
    for (index_t ix = 0; ix < nx; ++ix) {
        output << "# " << ix << "\n";
        for (index_t iy = 0; iy < ny; ++iy) {
            for (index_t iz = 0; iz < nz; ++iz) {
                output << Contents[GetIndex(ix, iy, iz)].Variance << " ";
            }
            output << "\n";
        }
    }
}

StatisticsContainer& Histogram3D::operator()(index_t& ix, index_t& iy, index_t& iz) {
    return Contents[GetIndex(ix, iy, iz)];
}

// Vector1D& Histogram3D::operator()(int& ix, int& iy) {
//     return Contents[ix][iy];
// }
// Vector2D& Histogram3D::operator()(int& ix) {
//     return Contents[ix];
// }

StatisticsContainer& Histogram3D::operator()(double& valx, double& valy, double& valz) {
    index_t ix = IndexMapX[static_cast<index_t>((valx - x_min) / (x_width))];
    index_t iy = IndexMapY[static_cast<index_t>((valy - y_min) / (y_width))];
    index_t iz = IndexMapZ[static_cast<index_t>((valz - z_min) / (z_width))];
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
        for (index_t ix = 0; ix < nx; ++ix) {
            for (index_t iy = 0; iy < ny; ++iy) {
                for (index_t iz = 0; iz < nz; ++iz) {
                    size_t index = GetIndex(ix, iy, iz);
                    Contents[index] += obj.Contents[index];
                }
            }
        }
    } else {
        cst::man::warning("Cannot add two Histograms(3D) of different sizes!\n");
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
    for (index_t ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        for (index_t iy = 0; iy < ny; ++iy) {
            std::getline(file, line);
            iss = std::istringstream(line);
            for (index_t iz = 0; iz < nz; ++iz) {
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
    for (index_t ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        for (index_t iy = 0; iy < ny; ++iy) {
            std::getline(file, line);
            iss = std::istringstream(line);
            for (index_t iz = 0; iz < nz; ++iz) {
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
    for (index_t ix = 0; ix < nx; ++ix) {
        std::getline(file, line);
        for (index_t iy = 0; iy < ny; ++iy) {
            std::getline(file, line);
            iss = std::istringstream(line);
            for (index_t iz = 0; iz < nz; ++iz) {
                iss >> Contents[GetIndex(ix, iy, iz)].EntryCount;
            }
        }
    }
    file.close();
}

}  // namespace Statistics
// }
