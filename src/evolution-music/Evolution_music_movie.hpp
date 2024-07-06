// Copyright (C) 2024 Lieuwe Huisman
#ifndef EVOLUTION_MUSIC_MOVIE_HPP
#define EVOLUTION_MUSIC_MOVIE_HPP

#include <omp.h>

#include <iostream>
#include <string>

#include "../Progressbar.hpp"
#include "../evolution-ampt/Evolution_ampt_utilities.hpp"
namespace MUSIC {
namespace Evolution {

std::streampos fileSize(const char *filePath) {
    std::streampos fsize = 0;
    std::ifstream file(filePath, std::ios::binary);

    fsize = file.tellg();
    file.seekg(0, std::ios::end);
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}

struct HeaderData {
    double tau0;
    double dtau;
    size_t nt;
    size_t nx;
    double xmin;
    double dx;
    size_t ny;
    double ymin;
    double dy;
    size_t neta;
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

struct CellData {
    float itau;
    float ix;
    float iy;
    float ieta;
    float volume;
    float epsilon;
    float rhob;
    float temp;
    float muB;
    float u1;
    float u2;
    float u3;
    float temptau;
    float JBtau;
    double posx;
    double posy;
    double energy;
    CellData(){};
    CellData(float header[14]) : itau(header[0]),
                                 ix(header[1]),
                                 iy(header[2]),
                                 ieta(header[3]),
                                 volume(header[4]),
                                 epsilon(header[5]),
                                 rhob(header[6]),
                                 temp(header[7]),
                                 muB(header[8]),
                                 u1(header[9]),
                                 u2(header[10]),
                                 u3(header[11]),
                                 temptau(header[12]),
                                 JBtau(header[13]) {}
    void GetProperties(HeaderData &header) {
        posx = header.xmin + ix * header.dx;
        posy = header.ymin + iy * header.dy;
        energy = volume * epsilon;
    }
};

bool Readline(std::ifstream &file, CellData &cell) {
    if (!file.read(reinterpret_cast<char *>(&cell.itau), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.ix), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.iy), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.ieta), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.volume), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.epsilon), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.rhob), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.temp), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.muB), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.u1), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.u2), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.u3), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.temptau), sizeof(float)))
        return false;
    if (!file.read(reinterpret_cast<char *>(&cell.JBtau), sizeof(float)))
        return false;
    return true;
}

class File {
   private:
    std::string datadirectory;
    std::string outputdirectory;

    HeaderData header;

    std::vector<std::unique_ptr<AMPT::Evolution::HistogramS2D>> energydensity;
    std::vector<std::unique_ptr<AMPT::Evolution::HistogramS2D>> temperature;
    AMPT::Evolution::Gridsettings Settings2D;
    bool grid_overwritten = false;

   public:
    File(std::string datadirectory_, std::string outputdirectory_) : datadirectory(datadirectory_), outputdirectory(outputdirectory_) {
    }

    void SetGrid(AMPT::Evolution::Gridsettings &settings) {
        Settings2D = settings;
        grid_overwritten = true;
    }

    void Parse() {
        std::ifstream file(datadirectory, std::ios::binary | std::ios::in);

        size_t filesize = fileSize(datadirectory.c_str());
        size_t expected_counts = (filesize - 12 * sizeof(float)) / (sizeof(float) * 14);

        float temp_header[12];
        // HeaderData header;
        file.read(reinterpret_cast<char *>(temp_header), sizeof(float) * 12);
        header = HeaderData(temp_header);
        if (!grid_overwritten) {
            Settings2D.xmin = header.xmin;
            Settings2D.ymin = header.ymin;

            Settings2D.dx = header.dx;
            Settings2D.dy = header.dy;
            Settings2D.xmax = header.xmin + header.dx * header.nx;
            Settings2D.ymax = header.ymin + header.dy * header.ny;
            Settings2D.nx = header.nx;
            Settings2D.ny = header.ny;
            // Settings2D.dvolume = header.volume;
        }
        // std::cout << Settings2D.dvolume << std::endl;

        // float temp_cell[14];
        float oldtau = -1;
        int counter = 0;

        size_t temp_cell_size = sizeof(float) * 14;

        std::vector<size_t> startpositions;

        size_t block_start_position = file.tellg();
        size_t linecounter;
        std::vector<size_t> linepositions;

        CellData temp_cell;

        Utilities::Progressbar progressbar(expected_counts);
        progressbar.Print();

        int expected_counts_fraction = expected_counts / 100 + 1;
        while (Readline(file, temp_cell)) {
            if (oldtau < temp_cell.itau) {
                linepositions.push_back(counter);
                block_start_position = (size_t)file.tellg() - 56;
                startpositions.push_back(block_start_position);
                // std::cout << temp_cell.volume << std::endl;
                oldtau = temp_cell.itau;
            }
            counter++;
            progressbar.Update();
            if (counter % expected_counts_fraction == 0 || counter == expected_counts) {
                progressbar.Print();
            }
        }
        std::cout << std::endl;
        linepositions.push_back(counter);
        file.close();

        header.nt = startpositions.size();

        std::vector<size_t> block_sizes;
        for (size_t i = 0; i < linepositions.size() - 1; i++) {
            block_sizes.push_back(linepositions[i + 1] - linepositions[i]);
        }
        energydensity.resize(startpositions.size());
        temperature.resize(startpositions.size());
        for (size_t i = 0; i < startpositions.size(); i++) {
            energydensity[i] = std::make_unique<AMPT::Evolution::HistogramS2D>(Settings2D.xmin, Settings2D.xmax, Settings2D.nx, Settings2D.ymin, Settings2D.ymax, Settings2D.ny);
            temperature[i] = std::make_unique<AMPT::Evolution::HistogramS2D>(Settings2D.xmin, Settings2D.xmax, Settings2D.nx, Settings2D.ymin, Settings2D.ymax, Settings2D.ny);
        }

        double volume_expansion_factor = header.dx * header.dy / (Settings2D.dx * Settings2D.dy);

        // std::cout << volume_expansion_factor << std::endl;
        progressbar.Initialize(startpositions.size());
        progressbar.Reset();
        progressbar.Print();
#pragma omp parallel for schedule(dynamic)
        for (size_t i = 0; i < startpositions.size(); i++) {
            std::ifstream file(datadirectory, std::ios::binary);
            CellData cell;
            file.seekg(startpositions[i]);
            for (int j = 0; j < block_sizes[i]; j++) {
                Readline(file, cell);
                cell.GetProperties(header);
                energydensity[i]->Add(cell.posx, cell.posy, cell.epsilon * volume_expansion_factor);
                temperature[i]->Add(cell.posx, cell.posy, cell.temp);
            }
            file.close();
            progressbar.Update();
#pragma omp critical
            {
                progressbar.Print();
            }
        }
        std::cout << std::endl;

        for (size_t i = 0; i < energydensity.size(); i++) {
            temperature[i]->CalculateAverage();
        }
    }
    // surface-time.dat
    // surface-energy-density-*.dat
    // surface-temperature-*.dat
    // surface-info.dat

    void Write(std::string directory) {
        // std::cout << directory << std::endl;
        std::string filename;
        std::ofstream file;

        filename = directory + "/surface-time.dat";
        file.open(filename, std::ios::out);
        for (size_t i = 0; i < header.nt; i++) {
            file << header.tau0 + i * header.dtau << "\n";
        }
        file.close();

        Utilities::Progressbar bar(header.nt);
        bar.Print();
#pragma omp parallel for schedule(dynamic)
        for (size_t it = 0; it < header.nt; ++it) {
            std::ofstream tfile;
            std::string tfilename;
            tfilename = directory + "/surface-temperature-" + std::to_string(it) + ".dat";
            tfile.open(tfilename);
            temperature[it]->PrintContents(tfile);
            tfile.close();

            tfilename = directory + "/surface-energy-density-" + std::to_string(it) + ".dat";
            tfile.open(tfilename);
            energydensity[it]->PrintContents(tfile);
            tfile.close();

            bar.Update();
#pragma omp critical
            {
                bar.Print();
            }
        }
        std::cout << std::endl;
    };
};

}  // namespace Evolution
}  // namespace MUSIC

#endif