#ifndef DATACONTAINER_HPP
#define DATACONTAINER_HPP

#include <algorithm>
#include <string>
#include <vector>

#include "ParticleProperties.hpp"
// #include "File_input.hpp"
#include "BinContainer.hpp"
#include "DataFormat.hpp"
#include "Histogram1D.hpp"
#include "Histogram3D.hpp"
#include "HistogramMap3D.hpp"
#include "Utilities.hpp"
// #include "HistogramSet.hpp"

#define DEFAULT_EXTENSION_HISTOGRAM "hist"

namespace Statistics {

template <typename T>
using PointerMap = std::map<std::string, std::unique_ptr<T>>;
template <typename T>
using VectorMap = std::map<std::string, T>;

class DataContainer {
   private:
    // Histogram definitions here.
    PointerMap<Statistics::Histogram1D> Histograms1D;
    PointerMap<Statistics::Histogram3D> Histograms3D;
    PointerMap<Statistics::HistogramMap3D> HistogramMaps3D;

    VectorMap<std::vector<double>> EdgesC;    // Centrality
    VectorMap<std::vector<double>> EdgesP;    // Participating nucleons
    VectorMap<std::vector<double>> EdgesRap;  // Rapidity
    VectorMap<std::vector<double>> EdgesPsR;  // Pseudorapidity
    VectorMap<std::vector<double>> EdgesMom;  // Transverse Momentum

    std::map<std::string, std::string> Filenames;

    std::vector<std::shared_ptr<Statistics::Block>> EventBlocks;

    unsigned int NumberOfBlocks = 0;

    std::string centrality_type;

    int nharmonic_min = 1;
    int nharmonic_max = NUMBER_OF_HARMONICS;

   public:
    DataContainer(){};

    // In derived classes this can be specified further.
    void InitialiseHistograms();

    void SetCentralityType(int collisiontype);

    void SetFlowRange(int nmin, int nmax);

    void AddParticle(Statistics::Block& block, Statistics::Line& line);

    void AddEvent(Statistics::Block& block);

    void AddEventBlock(std::shared_ptr<Statistics::Block> block);

    void ReserveEventBlocks(int reservesize);

    void ShrinkEventBlocks();

    void WriteData(std::string DataDirectory);

    void WriteEventData(std::string DataDirectory);

    void Add(DataContainer const& obj);

    void operator+=(DataContainer const& obj);
};

};  // namespace Statistics

#endif