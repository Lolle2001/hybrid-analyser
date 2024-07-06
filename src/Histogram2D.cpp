// Copyright (C) 2024 Lieuwe Huisman
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

void Histogram2D::Resize(size_t nx_, size_t ny_) {
    Contents.resize(nx_ * ny_);
}

std::string& Histogram2D::GetName() {
    return Name;
}

void Histogram2D::AddEvent() {
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            Contents[GetIndex(ix, iy)].AddEvent();
        }
    }
}

void Histogram2D::AddEventAverage() {
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            Contents[GetIndex(ix, iy)].AddEventSpecial();
        }
    }
}

void Histogram2D::Add(double valx, double valy, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max) {
        index_t ix = IndexMapX[(index_t)((valx - x_min) / (x_width))];
        index_t iy = IndexMapY[(index_t)((valy - y_min) / (y_width))];

        Contents[GetIndex(ix, iy)].Add(valcontent);
    }
}

void Histogram2D::AddCurrent(double valx, double valy, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max) {
        index_t ix = IndexMapX[(index_t)((valx - x_min) / (x_width))];
        index_t iy = IndexMapY[(index_t)((valy - y_min) / (y_width))];

        Contents[GetIndex(ix, iy)].AddCurrent(valcontent);
    }
}

void Histogram2D::Add(double valx, double valy, double valz, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max && valz >= z_min && valz < z_max) {
        index_t ix = IndexMapX[(index_t)((valx - x_min) / (x_width))];
        index_t iy = IndexMapY[(index_t)((valy - y_min) / (y_width))];

        Contents[GetIndex(ix, iy)].Add(valcontent);
    }
}

void Histogram2D::AddCurrent(double valx, double valy, double valz, double valcontent) {
    if (valx >= x_min && valx < x_max && valy >= y_min && valy < y_max && valz >= z_min && valz < z_max) {
        index_t ix = IndexMapX[(index_t)((valx - x_min) / (x_width))];
        index_t iy = IndexMapY[(index_t)((valy - y_min) / (y_width))];

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
    if (thirdaxis) {
        output << "nbins(z) = " << nz << "\n";
        output << "edges(z) = ";
        for (index_t iz = 0; iz <= nz; ++iz) {
            output << EdgesZ[iz] << " ";
        }
        output << "\n";
    }
}

void Histogram2D::PrintCount(std::ostream& output) {
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            output << std::setw(13) << std::right << Contents[GetIndex(ix, iy)].EntryCount << " ";
        }
        output << "\n";
    }
}
void Histogram2D::PrintTotalSQR(std::ostream& output) {
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            output << std::setw(13) << std::right << Contents[GetIndex(ix, iy)].TotalSQR << " ";
        }
        output << "\n";
    }
}

void Histogram2D::PrintTotal(std::ostream& output) {
    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            output << std::setw(13) << std::right << Contents[GetIndex(ix, iy)].Total << " ";
        }
        output << "\n";
    }
}
void Histogram2D::SetName(std::string XName_, std::string YName_, std::string ZName_, std::string CName_) {
    XName = XName_;
    YName = YName_;
    ZName = ZName_;
    CName = CName_;
}

void Histogram2D::PrintAll(std::ostream& output) {
    nlohmann::json j;

    std::vector<std::vector<double>> average(nx, std::vector<double>(ny, 0));
    std::vector<std::vector<double>> averagesqr(nx, std::vector<double>(ny, 0));
    std::vector<std::vector<double>> total(nx, std::vector<double>(ny, 0));
    std::vector<std::vector<double>> totalsqr(nx, std::vector<double>(ny, 0));
    std::vector<std::vector<double>> error(nx, std::vector<double>(ny, 0));
    std::vector<std::vector<size_t>> count(nx, std::vector<size_t>(ny, 0));

    for (index_t ix = 0; ix < nx; ++ix) {
        for (index_t iy = 0; iy < ny; ++iy) {
            index_t index = GetIndex(ix, iy);
            average[ix][iy] = Contents[index].Total / Contents[index].EntryCount;
            averagesqr[ix][iy] = Contents[index].TotalSQR / Contents[index].EntryCount;
            total[ix][iy] = Contents[index].Total;
            totalsqr[ix][iy] = Contents[index].TotalSQR;
            error[ix][iy] = std::sqrt(averagesqr[ix][iy] - average[ix][iy] * average[ix][iy]);
            count[ix][iy] = Contents[index].EntryCount;
        }
    }
    std::vector<double> xmids(nx);
    std::vector<double> ymids(ny);
    std::vector<double> xwids(nx);
    std::vector<double> ywids(ny);
    std::vector<double> xerr(nx);
    std::vector<double> yerr(ny);

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

    j["name"] = Name;
    j["settings"]["nbins"]["x"] = nx;
    j["settings"]["edges"]["x"] = EdgesX;
    j["settings"]["wids"]["x"] = xwids;
    j["settings"]["mids"]["x"] = xmids;
    j["settings"]["errs"]["x"] = xerr;
    j["settings"]["names"]["x"] = XName;

    j["settings"]["nbins"]["y"] = ny;
    j["settings"]["edges"]["y"] = EdgesY;
    j["settings"]["wids"]["y"] = ywids;
    j["settings"]["mids"]["y"] = ymids;
    j["settings"]["errs"]["y"] = yerr;
    j["settings"]["names"]["y"] = YName;
    if (thirdaxis) {
        j["settings"]["nbins"]["z"] = nz;
        j["settings"]["edges"]["z"] = EdgesZ;
        j["settings"]["wids"]["z"] = {z_max - z_min};
        j["settings"]["mids"]["z"] = {(z_max + z_min) / 2};
        j["settings"]["errs"]["z"] = {(z_max - z_min) / 2};
        j["settings"]["names"]["z"] = ZName;
    }

    j["settings"]["dimension"] = 2;
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
    j["contents"]["name"] = CName;

    output << j.dump(4);
}

StatisticsContainer& Histogram2D::operator()(index_t ix, index_t iy) {
    return Contents[GetIndex(ix, iy)];
}

// Vector1D& Histogram2D::operator()(int& ix) {
//     return Contents[ix];
// }

StatisticsContainer& Histogram2D::operator()(double valx, double valy) {
    index_t ix = IndexMapX[static_cast<index_t>((valx - x_min) / (x_width))];
    index_t iy = IndexMapY[static_cast<index_t>((valy - y_min) / (y_width))];

    return Contents[GetIndex(ix, iy)];
}
// Vector1D& Histogram2D::operator()(double& valx) {
//     int ix = IndexMapX[static_cast<int>((valx - x_min) / (x_width))];

//     return Contents[ix];
// }

void Histogram2D::operator+=(Histogram2D const& obj) {
    if (nx == obj.nx && ny == obj.ny) {
        for (index_t ix = 0; ix < nx; ++ix) {
            for (index_t iy = 0; iy < ny; ++iy) {
                index_t index = GetIndex(ix, iy);
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
    for (index_t ix = 0; ix < nx; ++ix) {
        std::getline(file, line);

        iss = std::istringstream(line);
        for (index_t iy = 0; iy < ny; ++iy) {
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
    for (index_t ix = 0; ix < nx; ++ix) {
        std::getline(file, line);

        iss = std::istringstream(line);
        for (index_t iy = 0; iy < ny; ++iy) {
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
    for (index_t ix = 0; ix < nx; ++ix) {
        std::getline(file, line);

        iss = std::istringstream(line);
        for (index_t iy = 0; iy < ny; ++iy) {
            iss >> Contents[GetIndex(ix, iy)].EntryCount;
        }
    }
    file.close();
}

}  // namespace Statistics
// }
