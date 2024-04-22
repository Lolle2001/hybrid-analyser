#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// #include "../Histogram2D.hpp"
// Assuming the same data types and parameters as in the writing function

struct CellData {
    double itau;
    double ix;
    double iy;
    double ieta;
    double volume;
    double epsilon;
    double rhob;
    double temp;
    double muB;
    double u1;
    double u2;
    double u3;
    double temptau;
    double JBtau;
};

struct HeaderData {
    double tau0;
    double dtau;
    int nx;
    double xmin;
    double dx;
    int ny;
    double ymin;
    double dy;
    int neta;
    double etamin;
    double deta;
    HeaderData(){};
    HeaderData(float header[12]) : tau0(header[0]),
                                   dtau(header[1]),
                                   nx(header[2]),
                                   dx(header[3]),
                                   xmin(header[4]),
                                   ny(header[5]),
                                   dy(header[6]),
                                   ymin(header[7]),
                                   neta(header[8]),
                                   deta(header[9]),
                                   etamin(header[10]){};
};
std::ostream& operator<<(std::ostream& output, std::vector<double>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        output << vec[i] << " ";
    }
    return output;
}

struct EvoData {
    std::vector<std::vector<std::vector<double>>> data;
    HeaderData header;

    EvoData(HeaderData header_) : header(header_){};

    void Append(std::vector<std::vector<double>>& vec) {
        data.push_back(vec);
    }

    void Write(std::ofstream& output) {
        output << "# " << data.size() << " " << header.nx << " " << header.ny << " " << header.neta << std::endl;
        output << "# " << header.dtau << " " << header.dx << " " << header.dy << " " << header.deta << std::endl;
        output << "# " << header.tau0 << " " << header.xmin << " " << header.ymin << " " << header.etamin << std::endl;

        for (int it = 0; it < data.size(); ++it) {
            for (int ix = 0; ix < header.nx; ++ix) {
                output << data[it][ix] << std::endl;
            }
        }
    }
};

void read_evolution_file(const std::string& filename, std::string outputname) {
    FILE* in_file_xyeta = fopen(filename.c_str(), "rb");
    if (!in_file_xyeta) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    float header[12];
    fread(header, sizeof(float), 12, in_file_xyeta);

    // Reading header information
    HeaderData headerdata(header);

    // std::cout << " tau0 " << header[0] << std::endl;
    // std::cout << " dtau " << header[1] << std::endl;

    // std::vector<double> EdgesX(output_nx + 1);
    // std::vector<double> EdgesY(output_ny + 1);

    // for (int ix = 0; ix < output_nx + 1; ++ix) {
    //     EdgesX[ix] = output_xmin + ix * output_dx;
    // }
    // for (int iy = 0; iy < output_ny + 1; ++iy) {
    //     EdgesY[iy] = output_xmin + iy * output_dx;
    // }

    // std::vector<Statistics::Histogram2D> histograms("evo.dat", EdgesX, EdgesY);

    // std::vector<std::vector<std::vector<double>>> histograms;

    // Reading cell data

    std::vector<float> data(14);
    int oldtau = 0;
    int counter = 0;

    EvoData histograms_temp(headerdata);
    EvoData histograms_energy(headerdata);

    std::vector<std::vector<double>> tempgrid(headerdata.nx, std::vector<double>(headerdata.ny, -1));
    std::vector<std::vector<double>> energygrid(headerdata.nx, std::vector<double>(headerdata.ny, -1));

    while (fread(data.data(), sizeof(float), 14, in_file_xyeta)) {
        tempgrid[data[1]][data[2]] = data[7];
        energygrid[data[1]][data[2]] = data[5];
        if (oldtau != data[0]) {
            oldtau = data[0];
            histograms_temp.Append(tempgrid);
            histograms_energy.Append(energygrid);
            tempgrid = std::vector<std::vector<double>>(headerdata.nx, std::vector<double>(headerdata.ny, -1));
            energygrid = std::vector<std::vector<double>>(headerdata.nx, std::vector<double>(headerdata.ny, -1));
        }
    }

    fclose(in_file_xyeta);
    std::stringstream name;
    name << "test/" << outputname << "_temp.dat";
    std::ofstream file(name.str());
    histograms_temp.Write(file);
    file.close();
    name.str("");
    name.clear();
    name << "test/" << outputname << "_energy.dat";
    file = std::ofstream(name.str());
    histograms_energy.Write(file);
    file.close();
}

int main(int argc, char** argv) {
    std::string runnumber = argv[1];
    std::string runbatch = argv[2];
    std::string name = argv[3];
    std::string datadirectory = "/home/lieuwe/Documents/Software/MUSIC/data";
    std::string filename = "evolution_for_movie_xyeta.dat";
    std::stringstream directory;
    directory << datadirectory << "/" << runnumber << "/" << runnumber << "_" << runbatch << "/" << filename;

    read_evolution_file(directory.str(), name);
    return 0;
}