// Copyright (C) 2024 Lieuwe Huisman
#ifndef DATACONTAINER_HPP
#define DATACONTAINER_HPP

#include <algorithm>
#include <string>
#include <vector>

#include "ParticleProperties.hpp"
// #include "File_input.hpp"

#include "DataFormat.hpp"
#include "Histogram1D.hpp"
#include "Histogram2D.hpp"
#include "Histogram3D.hpp"
#include "HistogramMap3D.hpp"
#include "Utilities.hpp"
// #include "HistogramSet.hpp"

#define DEFAULT_EXTENSION_HISTOGRAM "hist"

using size_s = unsigned int;

namespace Statistics {

template <typename T>
using PointerMap = std::map<std::string, std::unique_ptr<T>>;
template <typename T>
using VectorMap = std::map<std::string, T>;

class DataContainer {
   private:
    // Histogram definitions here.
    PointerMap<Statistics::Histogram1D> Histograms1D;
    PointerMap<Statistics::Histogram2D> Histograms2D;
    PointerMap<Statistics::Histogram3D> Histograms3D;
    PointerMap<Statistics::HistogramMap3D> HistogramMaps3D;

    VectorMap<std::vector<double>> EdgesC;    // Centrality
    VectorMap<std::vector<double>> EdgesP;    // Participating nucleons
    VectorMap<std::vector<double>> EdgesRap;  // Rapidity
    VectorMap<std::vector<double>> EdgesPsR;  // Pseudorapidity
    VectorMap<std::vector<double>> EdgesMom;  // Transverse Momentum

    std::vector<std::shared_ptr<Statistics::Block>> EventBlocks;

    size_t NumberOfBlocks = 0;

    std::string centrality_type;

    bool use_impactparameter_classification = false;

    size_t nharmonic_min = 1;
    size_t nharmonic_max = NUMBER_OF_HARMONICS;

    typedef double& (Statistics::Block::*FunctionPointer)();
    FunctionPointer funcptr;

   public:
    DataContainer(){

    };

    // In derived classes this can be specified further.

    void InitialiseBinning(bool use_impactparameter, int collisiontype);

    void InitialiseHistograms();

    void SetCentralityType(int collisiontype);

    void SetFlowRange(size_s nmin, size_s nmax);

    void AddParticle(Statistics::Block& block, Statistics::Line& line);

    void AddEvent(Statistics::Block& block);

    void AddEventBlock(std::shared_ptr<Statistics::Block> block);

    std::shared_ptr<Statistics::Block> GetEventBlock(int index) {
        return EventBlocks[index];
    }

    void ReserveEventBlocks(int reservesize);

    void ShrinkEventBlocks();

    void WriteData(std::string DataDirectory);

    void WriteEventData(std::string DataDirectory);

    void Add(DataContainer const& obj);

    void CalculateCentralityClasses();

    void SetCentralityEdges(std::string name, std::vector<double> edges) {
        // std::cout << edges.size() << std::endl;
        EdgesC[name] = edges;
    };
    std::vector<double> GetCentralityEdges(std::string name) {
        return EdgesC[name];
    };

    void InsertBlocks(DataContainer const& obj) {
        EventBlocks.insert(std::end(EventBlocks), std::begin(obj.EventBlocks), std::end(obj.EventBlocks));
        NumberOfBlocks += obj.NumberOfBlocks;
        // for (const auto& block : obj.EventBlocks) {
        //     EventBlocks.push_back(std::make_shared<Statistics::Block>(*block));
        // }
    }

    void operator+=(DataContainer const& obj);
};

};  // namespace Statistics

#endif