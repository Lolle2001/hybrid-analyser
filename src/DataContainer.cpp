#include "DataContainer.hpp"

namespace Statistics {

// In derived classes this can be specified further.

void DataContainer::SetFlowRange(int nmin, int nmax){

};

void DataContainer::ReserveEventBlocks(int reservesize){

};

void DataContainer::ShrinkEventBlocks(){

};

void DataContainer::SetCentralityType(int collisiontype) {
    funcptr = &Statistics::Block::GetImpactParameter;
    if (collisiontype == 0) {
        centrality_type = "1:PbPb5020";
    } else if (collisiontype == 1) {
        centrality_type = "1:pPb5020";
    } else if (collisiontype == 2) {
        centrality_type = "1:pp5020";
    } else if (collisiontype == 3) {
        centrality_type = "ncharged";
        funcptr = &Statistics::Block::GetNumberOfChargedParticles;
    } else if (collisiontype == 4) {
        centrality_type = "2:PbPb5020";
    } else {
        centrality_type = "1:PbPb5020";
    }
}

void DataContainer::WriteData(std::string DataDirectory) {
    std::stringstream Filename;
    std::ofstream File;
    double Filesize;

    for (const auto &entry : Histograms3D) {
        Filename << DataDirectory << "/" << Histograms3D[entry.first]->GetName() << "_"
                 << "COUNT"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms3D[entry.first]->PrintCount(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Histograms3D[entry.first]->GetName() << "_"
                 << "TOTAL"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms3D[entry.first]->PrintTotal(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Histograms3D[entry.first]->GetName() << "_"
                 << "TOTALSQR"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms3D[entry.first]->PrintTotalSQR(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Histograms3D[entry.first]->GetName() << "_"
                 << "VARIANCE"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms3D[entry.first]->PrintVariance(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Histograms3D[entry.first]->GetName() << "_"
                 << "SETTINGS"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms3D[entry.first]->PrintEdges(File);
        File.close();
        Filename.str("");
        Filename.clear();
    }

    for (const auto &entry : Histograms2D) {
        Filename << DataDirectory << "/" << Histograms2D[entry.first]->GetName() << "_"
                 << "COUNT"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms2D[entry.first]->PrintCount(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Histograms2D[entry.first]->GetName() << "_"
                 << "TOTAL"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms2D[entry.first]->PrintTotal(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Histograms2D[entry.first]->GetName() << "_"
                 << "TOTALSQR"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms2D[entry.first]->PrintTotalSQR(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Histograms2D[entry.first]->GetName() << "_"
                 << "SETTINGS"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms2D[entry.first]->PrintEdges(File);
        File.close();
        Filename.str("");
        Filename.clear();
    }
    for (const auto &entry : Histograms1D) {
        Filename << DataDirectory << "/" << Histograms1D[entry.first]->GetName() << "_"
                 << "COUNT"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms1D[entry.first]->PrintCount(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Histograms1D[entry.first]->GetName() << "_"
                 << "TOTAL"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms1D[entry.first]->PrintTotal(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Histograms1D[entry.first]->GetName() << "_"
                 << "TOTALSQR"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms1D[entry.first]->PrintTotalSQR(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Histograms1D[entry.first]->GetName() << "_"
                 << "SETTINGS"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms1D[entry.first]->PrintEdges(File);
        File.close();
        Filename.str("");
        Filename.clear();
    }
    for (const auto &entry : HistogramMaps3D) {
        HistogramMaps3D[entry.first]->Convert();
        Filename << DataDirectory << "/" << HistogramMaps3D[entry.first]->GetName() << "_"
                 << "COUNT"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        HistogramMaps3D[entry.first]->PrintCount(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << HistogramMaps3D[entry.first]->GetName() << "_"
                 << "TOTAL"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        HistogramMaps3D[entry.first]->PrintTotal(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << HistogramMaps3D[entry.first]->GetName() << "_"
                 << "TOTALSQR"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        HistogramMaps3D[entry.first]->PrintTotalSQR(File);
        File.close();
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << HistogramMaps3D[entry.first]->GetName() << "_"
                 << "SETTINGS"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        HistogramMaps3D[entry.first]->PrintEdges(File);
        File.close();
        Filename.str("");
        Filename.clear();
    }
};

void DataContainer::WriteEventData(std::string DataDirectory) {
    std::stringstream Filename;
    std::ofstream File;
    double Filesize;

    Filename << DataDirectory << "/"
             << "eventinfo"
             << "." << DEFAULT_EXTENSION_HISTOGRAM;
    File.open(Filename.str(), std::ios::out);

    for (int i = 0; i < NumberOfBlocks; ++i) {
        EventBlocks[i]->Write(File);

        File << "\n";
    }

    File.close();
    Filename.str("");
    Filename.clear();
};

void DataContainer::Add(DataContainer const &obj) {
    for (const auto &entry : Histograms1D) {
        if (Histograms1D.find(entry.first) != Histograms1D.end() &&
            obj.Histograms1D.find(entry.first) != obj.Histograms1D.end()) {
            *Histograms1D.at(entry.first) += *obj.Histograms1D.at(entry.first);

        } else {
#pragma omp critical
            {
                printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
                printf("%s\n", "Cannot add file object");
                fflush(stdout);
            }
        }
    }
    for (const auto &entry : Histograms2D) {
        if (Histograms2D.find(entry.first) != Histograms2D.end() &&
            obj.Histograms2D.find(entry.first) != obj.Histograms2D.end()) {
            // Check if both histograms exist before attempting to add them
            *Histograms2D.at(entry.first) += *obj.Histograms2D.at(entry.first);

        } else {
#pragma omp critical
            {
                printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
                printf("%s\n", "Cannot add file object");
                fflush(stdout);
            }
        }
    }

    for (const auto &entry : Histograms3D) {
        if (Histograms3D.find(entry.first) != Histograms3D.end() &&
            obj.Histograms3D.find(entry.first) != obj.Histograms3D.end()) {
            // Check if both histograms exist before attempting to add them
            *Histograms3D.at(entry.first) += *obj.Histograms3D.at(entry.first);
            // std::cout << entry.first << " " << Histograms3D[entry.first]->GetContent(0, 0, 0).EntryCount << std::endl;

        }

        else {
#pragma omp critical
            {
                printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
                printf("%s\n", "Cannot add file object");
                fflush(stdout);
            }
        }
    }

    for (const auto &entry : HistogramMaps3D) {
        if (HistogramMaps3D.find(entry.first) != HistogramMaps3D.end() && obj.HistogramMaps3D.find(entry.first) != obj.HistogramMaps3D.end()) {
            *HistogramMaps3D.at(entry.first) += *obj.HistogramMaps3D.at(entry.first);
        } else {
#pragma omp critical
            {
                printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
                printf("%s\n", "Cannot add file object");
                fflush(stdout);
            }
        }
    }

    EventBlocks.insert(std::end(EventBlocks), std::begin(obj.EventBlocks), std::end(obj.EventBlocks));

    NumberOfBlocks += obj.NumberOfBlocks;
    int StartIndex = NumberOfBlocks - obj.NumberOfBlocks;
    // std::cout << EventBlocks.size() << std::endl;
    // std::cout << StartIndex << std::endl;

    for (int i = StartIndex; i < NumberOfBlocks; ++i) {
        EventBlocks[i]->SetEventID(EventBlocks[i]->GetEventID() + StartIndex);
    }
};

void DataContainer::operator+=(DataContainer const &obj) {
    Add(obj);
};

void DataContainer::InitialiseBinning(bool use_impactparameter, int collisiontype) {
    if (use_impactparameter) {
        if (collisiontype == 0) {
            centrality_type = "1:PbPb5020";
        } else if (collisiontype == 1) {
            centrality_type = "1:pPb5020";
        } else if (collisiontype == 2) {
            centrality_type = "1:pp5020";

        } else {
            centrality_type = "1:PbPb5020";
        }
    } else {
        centrality_type = "ncharged";
    }
}

void DataContainer::InitialiseHistograms() {
    EdgesC["1:PbPb5020"] = (std::vector<double>){0.00, 3.49, 4.93, 6.98, 8.55, 9.87, 11.00, 12.10, 13.10, 14.00, 14.90, 20.00};  // From MC Glauber model
    EdgesC["2:PbPb5020"] = (std::vector<double>){0.00, 3.50, 5.00, 7.20, 8.80, 10.2, 11.40, 12.50, 13.60, 14.60, 15.50, 20.00};  // From trajectum
    EdgesC["3:PbPb5020"] = (std::vector<double>){0.00, 3.49, 4.93, 6.04, 6.98, 7.80, 8.55, 9.23, 9.87, 10.50, 11.00, 11.60, 12.10, 12.60, 13.10, 13.50, 14.00, 14.40, 14.90, 15.60, 20.00};
    EdgesC["1:pPb5020"] = (std::vector<double>){0.00, 1.82, 2.58, 3.65, 4.47, 5.16, 5.77, 6.32, 6.84, 7.36, 7.99, 14.70};
    EdgesC["1:pp5020"] = (std::vector<double>){0.00, 20.00};

    // Evenstatistics
    Histograms1D["impactparameter_1"] = std::make_unique<Histogram1D>("impactparameter_1", EdgesC[centrality_type]);
    Histograms1D["participation_1"] = std::make_unique<Histogram1D>("participation_1", EdgesC[centrality_type]);
    Histograms1D["binarycollisions_1"] = std::make_unique<Histogram1D>("binarycollisions_1", EdgesC[centrality_type]);

    Histograms1D["impactparameter_2"] = std::make_unique<Histogram1D>("impactparameter_2", EdgesC["ncharged"]);
    Histograms1D["participation_2"] = std::make_unique<Histogram1D>("participation_2", EdgesC["ncharged"]);
    Histograms1D["binarycollisions_2"] = std::make_unique<Histogram1D>("binarycollisions_2", EdgesC["ncharged"]);

    // Transverse momentum spectra as function of pT and centrality for mid rapidity
    EdgesRap["1:p_pbar"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:p_pbar"] = (std::vector<double>){0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2., 2.2, 2.4, 2.6, 2.8, 3., 3.2, 3.4, 3.6, 3.8, 4., 4.5, 5., 5.5, 6., 6.5, 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 18., 20.};
    EdgesRap["1:K+_K-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:K+_K-"] = (std::vector<double>){0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2., 2.2, 2.4, 2.6, 2.8, 3., 3.2, 3.4, 3.6, 3.8, 4., 4.5, 5., 5.5, 6., 6.5, 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 18., 20.};
    EdgesRap["1:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:pi+_pi-"] = (std::vector<double>){0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2., 2.2, 2.4, 2.6, 2.8, 3., 3.2, 3.4, 3.6, 3.8, 4., 4.5, 5., 5.5, 6., 6.5, 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 18., 20.};
    EdgesRap["1:charged"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:charged"] = (std::vector<double>){0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2., 2.2, 2.4, 2.6, 2.8, 3., 3.2, 3.4, 3.6, 3.8, 4., 4.5, 5., 5.5, 6., 6.5, 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 18., 20.};

    Histograms2D["dNdptdy_1_charged"] = std::make_unique<Histogram2D>("dNdptdy_1_charged", EdgesC[centrality_type], EdgesMom["1:charged"], EdgesRap["1:charged"]);
    Histograms2D["dNdptdy_1_chpions"] = std::make_unique<Histogram2D>("dNdptdy_1_chpions", EdgesC[centrality_type], EdgesMom["1:pi+_pi-"], EdgesRap["1:pi+_pi-"]);
    Histograms2D["dNdptdy_1_chkaons"] = std::make_unique<Histogram2D>("dNdptdy_1_chkaons", EdgesC[centrality_type], EdgesMom["1:K+_K-"], EdgesRap["1:K+_K-"]);
    Histograms2D["dNdptdy_1_chprotons"] = std::make_unique<Histogram2D>("dNdptdy_1_chprotons", EdgesC[centrality_type], EdgesMom["1:p_pbar"], EdgesRap["1:p_pbar"]);

    EdgesRap["2:p_pbar"] = (std::vector<double>){-0.8, 0.8};
    EdgesRap["2:K+_K-"] = (std::vector<double>){-0.8, 0.8};
    EdgesRap["2:pi+_pi-"] = (std::vector<double>){-0.8, 0.8};
    EdgesRap["2:charged"] = (std::vector<double>){-0.8, 0.8};

    Histograms2D["dNdptdeta_1_charged"] = std::make_unique<Histogram2D>("dNdptdeta_1_charged", EdgesC[centrality_type], EdgesMom["1:charged"], EdgesRap["2:charged"]);
    Histograms2D["dNdptdeta_1_chpions"] = std::make_unique<Histogram2D>("dNdptdeta_1_chpions", EdgesC[centrality_type], EdgesMom["1:pi+_pi-"], EdgesRap["2:pi+_pi-"]);
    Histograms2D["dNdptdeta_1_chkaons"] = std::make_unique<Histogram2D>("dNdptdeta_1_chkaons", EdgesC[centrality_type], EdgesMom["1:K+_K-"], EdgesRap["2:K+_K-"]);
    Histograms2D["dNdptdeta_1_chprotons"] = std::make_unique<Histogram2D>("dNdptdeta_1_chprotons", EdgesC[centrality_type], EdgesMom["1:p_pbar"], EdgesRap["2:p_pbar"]);

    // Average pt for low pT
    EdgesRap["1:meanpt"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:meanpt"] = (std::vector<double>){0., 3.};

    Histograms1D["meanpt_1_chprotons"] = std::make_unique<Histogram1D>("meanpt_1_chprotons", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms1D["meanpt_1_chkaons"] = std::make_unique<Histogram1D>("meanpt_1_chkaons", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms1D["meanpt_1_chpions"] = std::make_unique<Histogram1D>("meanpt_1_chpions", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms1D["meanpt_1_charged"] = std::make_unique<Histogram1D>("meanpt_1_charged", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);

    Histograms1D["meanpt_2_chprotons"] = std::make_unique<Histogram1D>("meanpt_2_chprotons", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms1D["meanpt_2_chkaons"] = std::make_unique<Histogram1D>("meanpt_2_chkaons", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms1D["meanpt_2_chpions"] = std::make_unique<Histogram1D>("meanpt_2_chpions", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms1D["meanpt_2_charged"] = std::make_unique<Histogram1D>("meanpt_2_charged", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);

    Histograms1D["meanpt_3_chprotons"] = std::make_unique<Histogram1D>("meanpt_2_chprotons", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms1D["meanpt_3_chkaons"] = std::make_unique<Histogram1D>("meanpt_2_chkaons", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms1D["meanpt_3_chpions"] = std::make_unique<Histogram1D>("meanpt_2_chpions", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms1D["meanpt_3_charged"] = std::make_unique<Histogram1D>("meanpt_2_charged", EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);

    // Average yield for low pT
    EdgesRap["1:meanyield"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:meanyield"] = (std::vector<double>){0., 3.};

    Histograms1D["meanyield_1_chprotons"] = std::make_unique<Histogram1D>("meanyield_1_chprotons", EdgesC[centrality_type], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyield_1_chkaons"] = std::make_unique<Histogram1D>("meanyield_1_chkaons", EdgesC[centrality_type], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyield_1_chpions"] = std::make_unique<Histogram1D>("meanyield_1_chpions", EdgesC[centrality_type], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyield_1_charged"] = std::make_unique<Histogram1D>("meanyield_1_charged", EdgesC[centrality_type], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);

    Histograms1D["meanyield_2_chprotons"] = std::make_unique<Histogram1D>("meanyield_2_chprotons", EdgesC["ncharged"], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyield_2_chkaons"] = std::make_unique<Histogram1D>("meanyield_2_chkaons", EdgesC["ncharged"], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyield_2_chpions"] = std::make_unique<Histogram1D>("meanyield_2_chpions", EdgesC["ncharged"], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyield_2_charged"] = std::make_unique<Histogram1D>("meanyield_2_charged", EdgesC["ncharged"], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);

    Histograms1D["meanyield_3_chprotons"] = std::make_unique<Histogram1D>("meanyield_3_chprotons", EdgesC["1:PbPb5020"], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyield_3_chkaons"] = std::make_unique<Histogram1D>("meanyield_3_chkaons", EdgesC["1:PbPb5020"], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyield_3_chpions"] = std::make_unique<Histogram1D>("meanyield_3_chpions", EdgesC["1:PbPb5020"], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyield_3_charged"] = std::make_unique<Histogram1D>("meanyield_3_charged", EdgesC["1:PbPb5020"], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);

    Histograms1D["meanyieldeta_1_chprotons"] = std::make_unique<Histogram1D>("meanyieldeta_1_chprotons", EdgesC[centrality_type], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyieldeta_1_chkaons"] = std::make_unique<Histogram1D>("meanyieldeta_1_chkaons", EdgesC[centrality_type], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyieldeta_1_chpions"] = std::make_unique<Histogram1D>("meanyieldeta_1_chpions", EdgesC[centrality_type], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    Histograms1D["meanyieldeta_1_charged"] = std::make_unique<Histogram1D>("meanyieldeta_1_charged", EdgesC[centrality_type], EdgesMom["1:meanyield"], EdgesRap["1:meanyield"]);
    // Rapidity spectra as function of y and centrality for all pT and low pT
    EdgesRap["3:p_pbar"] = (std::vector<double>){-10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
    EdgesMom["3:p_pbar"] = (std::vector<double>){0.01, 20.};
    EdgesRap["3:K+_K-"] = (std::vector<double>){-10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
    EdgesMom["3:K+_K-"] = (std::vector<double>){0.01, 20.};
    EdgesRap["3:pi+_pi-"] = (std::vector<double>){-10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
    EdgesMom["3:pi+_pi-"] = (std::vector<double>){0.01, 20.};
    EdgesRap["3:charged"] = (std::vector<double>){-10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
    EdgesMom["3:charged"] = (std::vector<double>){0.01, 20.};

    Histograms2D["dNdy_1_charged"] = std::make_unique<Histogram2D>("dNdy_1_charged", EdgesC[centrality_type], EdgesRap["3:charged"], EdgesMom["3:charged"]);
    Histograms2D["dNdy_1_chpions"] = std::make_unique<Histogram2D>("dNdy_1_chpions", EdgesC[centrality_type], EdgesRap["3:pi+_pi-"], EdgesMom["3:pi+_pi-"]);
    Histograms2D["dNdy_1_chkaons"] = std::make_unique<Histogram2D>("dNdy_1_chkaons", EdgesC[centrality_type], EdgesRap["3:K+_K-"], EdgesMom["3:K+_K-"]);
    Histograms2D["dNdy_1_chprotons"] = std::make_unique<Histogram2D>("dNdy_1_chprotons", EdgesC[centrality_type], EdgesRap["3:p_pbar"], EdgesMom["3:p_pbar"]);

    Histograms2D["dNdeta_1_charged"] = std::make_unique<Histogram2D>("dNdeta_1_charged", EdgesC[centrality_type], EdgesRap["3:charged"], EdgesMom["3:charged"]);
    Histograms2D["dNdeta_1_chpions"] = std::make_unique<Histogram2D>("dNdeta_1_chpions", EdgesC[centrality_type], EdgesRap["3:pi+_pi-"], EdgesMom["3:pi+_pi-"]);
    Histograms2D["dNdeta_1_chkaons"] = std::make_unique<Histogram2D>("dNdeta_1_chkaons", EdgesC[centrality_type], EdgesRap["3:K+_K-"], EdgesMom["3:K+_K-"]);
    Histograms2D["dNdeta_1_chprotons"] = std::make_unique<Histogram2D>("dNdeta_1_chprotons", EdgesC[centrality_type], EdgesRap["3:p_pbar"], EdgesMom["3:p_pbar"]);

    EdgesMom["4:p_pbar"] = (std::vector<double>){0.0, 3.};
    EdgesMom["4:K+_K-"] = (std::vector<double>){0.0, 3.};
    EdgesMom["4:pi+_pi-"] = (std::vector<double>){0.0, 3.};
    EdgesMom["4:charged"] = (std::vector<double>){0.0, 3.};

    Histograms2D["dNdy_2_charged"] = std::make_unique<Histogram2D>("dNdy_2_charged", EdgesC[centrality_type], EdgesRap["3:charged"], EdgesMom["4:charged"]);
    Histograms2D["dNdy_2_chpions"] = std::make_unique<Histogram2D>("dNdy_2_chpions", EdgesC[centrality_type], EdgesRap["3:pi+_pi-"], EdgesMom["4:pi+_pi-"]);
    Histograms2D["dNdy_2_chkaons"] = std::make_unique<Histogram2D>("dNdy_2_chkaons", EdgesC[centrality_type], EdgesRap["3:K+_K-"], EdgesMom["4:K+_K-"]);
    Histograms2D["dNdy_2_chprotons"] = std::make_unique<Histogram2D>("dNdy_2_chprotons", EdgesC[centrality_type], EdgesRap["3:p_pbar"], EdgesMom["4:p_pbar"]);

    Histograms2D["dNdeta_2_charged"] = std::make_unique<Histogram2D>("dNdeta_2_charged", EdgesC[centrality_type], EdgesRap["3:charged"], EdgesMom["4:charged"]);
    Histograms2D["dNdeta_2_chpions"] = std::make_unique<Histogram2D>("dNdeta_2_chpions", EdgesC[centrality_type], EdgesRap["3:pi+_pi-"], EdgesMom["4:pi+_pi-"]);
    Histograms2D["dNdeta_2_chkaons"] = std::make_unique<Histogram2D>("dNdeta_2_chkaons", EdgesC[centrality_type], EdgesRap["3:K+_K-"], EdgesMom["4:K+_K-"]);
    Histograms2D["dNdeta_2_chprotons"] = std::make_unique<Histogram2D>("dNdeta_2_chprotons", EdgesC[centrality_type], EdgesRap["3:p_pbar"], EdgesMom["4:p_pbar"]);

    // Anisotropic flow as function of pT and centrality for mid rapidity
    EdgesRap["5:p_pbar"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["5:p_pbar"] = (std::vector<double>){0.5, 1., 1.5, 2., 2.5, 3., 4., 6.};
    EdgesRap["5:K+_K-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["5:K+_K-"] = (std::vector<double>){0.3, 0.6, 1., 1.5, 2., 2.5, 3., 4., 6.};
    EdgesRap["5:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["5:pi+_pi-"] = (std::vector<double>){0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1., 1.25, 1.5, 1.75, 2., 2.25, 2.5, 3., 3.5, 4., 5., 6., 8., 10.};
    EdgesRap["5:charged"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["5:charged"] = (std::vector<double>){0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1., 1.25, 1.5, 1.75, 2., 2.25, 2.5, 3., 3.5, 4., 5., 6., 8., 10.};

    Histograms2D["v2pT_1_chprotons"] = std::make_unique<Histogram2D>("v2pT_1_chprotons", EdgesC[centrality_type], EdgesMom["5:p_pbar"], EdgesRap["5:p_pbar"]);
    Histograms2D["v2pT_1_chpions"] = std::make_unique<Histogram2D>("v2pT_1_chpions", EdgesC[centrality_type], EdgesMom["5:pi+_pi-"], EdgesRap["5:pi+_pi-"]);
    Histograms2D["v2pT_1_chkaons"] = std::make_unique<Histogram2D>("v2pT_1_chkaons", EdgesC[centrality_type], EdgesMom["5:K+_K-"], EdgesRap["5:K+_K-"]);
    Histograms2D["v2pT_1_charged"] = std::make_unique<Histogram2D>("v2pT_1_charged", EdgesC[centrality_type], EdgesMom["5:charged"], EdgesRap["5:charged"]);

    // Histograms2D["v3pT_1_chprotons"] = std::make_unique<Histogram2D>("v3pT_1_chprotons", EdgesC[centrality_type], EdgesMom["5:p_pbar"], EdgesRap["5:p_pbar"]);
    // Histograms2D["v3pT_1_chpions"] = std::make_unique<Histogram2D>("v3pT_1_chpions", EdgesC[centrality_type], EdgesMom["5:pi+_pi-"], EdgesRap["5:pi+_pi-"]);
    // Histograms2D["v3pT_1_chkaons"] = std::make_unique<Histogram2D>("v3pT_1_chkaons", EdgesC[centrality_type], EdgesMom["5:K+_K-"], EdgesRap["5:K+_K-"]);
    // Histograms2D["v3pT_1_charged"] = std::make_unique<Histogram2D>("v3pT_1_charged", EdgesC[centrality_type], EdgesMom["5:charged"], EdgesRap["5:charged"]);

    // Histograms2D["v4pT_1_chprotons"] = std::make_unique<Histogram2D>("v4pT_1_chprotons", EdgesC[centrality_type], EdgesMom["5:p_pbar"], EdgesRap["5:p_pbar"]);
    // Histograms2D["v4pT_1_chpions"] = std::make_unique<Histogram2D>("v4pT_1_chpions", EdgesC[centrality_type], EdgesMom["5:pi+_pi-"], EdgesRap["5:pi+_pi-"]);
    // Histograms2D["v4pT_1_chkaons"] = std::make_unique<Histogram2D>("v4pT_1_chkaons", EdgesC[centrality_type], EdgesMom["5:K+_K-"], EdgesRap["5:K+_K-"]);
    // Histograms2D["v4pT_1_charged"] = std::make_unique<Histogram2D>("v4pT_1_charged", EdgesC[centrality_type], EdgesMom["5:charged"], EdgesRap["5:charged"]);

    // Histograms2D["v5pT_1_chprotons"] = std::make_unique<Histogram2D>("v5pT_1_chprotons", EdgesC[centrality_type], EdgesMom["5:p_pbar"], EdgesRap["5:p_pbar"]);
    // Histograms2D["v5pT_1_chpions"] = std::make_unique<Histogram2D>("v5pT_1_chpions", EdgesC[centrality_type], EdgesMom["5:pi+_pi-"], EdgesRap["5:pi+_pi-"]);
    // Histograms2D["v5pT_1_chkaons"] = std::make_unique<Histogram2D>("v5pT_1_chkaons", EdgesC[centrality_type], EdgesMom["5:K+_K-"], EdgesRap["5:K+_K-"]);
    // Histograms2D["v5pT_1_charged"] = std::make_unique<Histogram2D>("v5pT_1_charged", EdgesC[centrality_type], EdgesMom["5:charged"], EdgesRap["5:charged"]);

    EdgesRap["v2pT:2:p_pbar"] = (std::vector<double>){-1, 1};
    EdgesMom["v2pT:2:p_pbar"] = (std::vector<double>){0, 0.25, 0.5, 0.75, 1., 1.25, 1.5, 1.75, 2., 2.25, 2.5, 2.75, 3., 3.25, 3.5, 3.75, 4., 5., 6.};
    EdgesRap["v2pT:2:K+_K-"] = (std::vector<double>){-1, 1};
    EdgesMom["v2pT:2:K+_K-"] = (std::vector<double>){0, 0.25, 0.5, 0.75, 1., 1.25, 1.5, 1.75, 2., 2.25, 2.5, 2.75, 3., 3.25, 3.5, 3.75, 4., 5., 6.};
    EdgesRap["v2pT:2:pi+_pi-"] = (std::vector<double>){-1, 1};
    EdgesMom["v2pT:2:pi+_pi-"] = (std::vector<double>){0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1., 1.25, 1.5, 1.75, 2., 2.25, 2.5, 2.75, 3., 3.25, 3.5, 3.75, 4., 5., 6., 8., 10.};
    EdgesRap["v2pT:2:charged"] = (std::vector<double>){-1, 1};
    EdgesMom["v2pT:2:charged"] = (std::vector<double>){0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1., 1.25, 1.5, 1.75, 2., 2.25, 2.5, 2.75, 3., 3.25, 3.5, 3.75, 4., 5., 6., 8., 10.};

    Histograms2D["v2pT_2_chprotons"] = std::make_unique<Histogram2D>("v2pT_2_chprotons", EdgesC[centrality_type], EdgesMom["v2pT:2:p_pbar"], EdgesRap["v2pT:2:p_pbar"]);
    Histograms2D["v2pT_2_chpions"] = std::make_unique<Histogram2D>("v2pT_2_chpions", EdgesC[centrality_type], EdgesMom["v2pT:2:pi+_pi-"], EdgesRap["v2pT:2:pi+_pi-"]);
    Histograms2D["v2pT_2_chkaons"] = std::make_unique<Histogram2D>("v2pT_2_chkaons", EdgesC[centrality_type], EdgesMom["v2pT:2:K+_K-"], EdgesRap["v2pT:2:K+_K-"]);
    Histograms2D["v2pT_2_charged"] = std::make_unique<Histogram2D>("v2pT_2_charged", EdgesC[centrality_type], EdgesMom["v2pT:2:charged"], EdgesRap["v2pT:2:charged"]);

    // Histograms2D["v3pT_2_chprotons"] = std::make_unique<Histogram2D>("v3pT_2_chprotons", EdgesC[centrality_type], EdgesMom["v2pT:2:p_pbar"], EdgesRap["v2pT:2:p_pbar"]);
    // Histograms2D["v3pT_2_chpions"] = std::make_unique<Histogram2D>("v3pT_2_chpions", EdgesC[centrality_type], EdgesMom["v2pT:2:pi+_pi-"], EdgesRap["v2pT:2:pi+_pi-"]);
    // Histograms2D["v3pT_2_chkaons"] = std::make_unique<Histogram2D>("v3pT_2_chkaons", EdgesC[centrality_type], EdgesMom["v2pT:2:K+_K-"], EdgesRap["v2pT:2:K+_K-"]);
    // Histograms2D["v3pT_2_charged"] = std::make_unique<Histogram2D>("v3pT_2_charged", EdgesC[centrality_type], EdgesMom["v2pT:2:charged"], EdgesRap["v2pT:2:charged"]);

    // Histograms2D["v4pT_2_chprotons"] = std::make_unique<Histogram2D>("v4pT_2_chprotons", EdgesC[centrality_type], EdgesMom["v2pT:2:p_pbar"], EdgesRap["v2pT:2:p_pbar"]);
    // Histograms2D["v4pT_2_chpions"] = std::make_unique<Histogram2D>("v4pT_2_chpions", EdgesC[centrality_type], EdgesMom["v2pT:2:pi+_pi-"], EdgesRap["v2pT:2:pi+_pi-"]);
    // Histograms2D["v4pT_2_chkaons"] = std::make_unique<Histogram2D>("v4pT_2_chkaons", EdgesC[centrality_type], EdgesMom["v2pT:2:K+_K-"], EdgesRap["v2pT:2:K+_K-"]);
    // Histograms2D["v4pT_2_charged"] = std::make_unique<Histogram2D>("v4pT_2_charged", EdgesC[centrality_type], EdgesMom["v2pT:2:charged"], EdgesRap["v2pT:2:charged"]);

    // Histograms2D["v5pT_2_chprotons"] = std::make_unique<Histogram2D>("v5pT_2_chprotons", EdgesC[centrality_type], EdgesMom["v2pT:2:p_pbar"], EdgesRap["v2pT:2:p_pbar"]);
    // Histograms2D["v5pT_2_chpions"] = std::make_unique<Histogram2D>("v5pT_2_chpions", EdgesC[centrality_type], EdgesMom["v2pT:2:pi+_pi-"], EdgesRap["v2pT:2:pi+_pi-"]);
    // Histograms2D["v5pT_2_chkaons"] = std::make_unique<Histogram2D>("v5pT_2_chkaons", EdgesC[centrality_type], EdgesMom["v2pT:2:K+_K-"], EdgesRap["v2pT:2:K+_K-"]);
    // Histograms2D["v5pT_2_charged"] = std::make_unique<Histogram2D>("v5pT_2_charged", EdgesC[centrality_type], EdgesMom["v2pT:2:charged"], EdgesRap["v2pT:2:charged"]);

    Histograms2D["v2pT_3_chprotons"] = std::make_unique<Histogram2D>("v2pT_3_chprotons", EdgesC[centrality_type], EdgesMom["v2pT:2:p_pbar"], EdgesRap["v2pT:2:p_pbar"]);
    Histograms2D["v2pT_3_chpions"] = std::make_unique<Histogram2D>("v2pT_3_chpions", EdgesC[centrality_type], EdgesMom["v2pT:2:pi+_pi-"], EdgesRap["v2pT:2:pi+_pi-"]);
    Histograms2D["v2pT_3_chkaons"] = std::make_unique<Histogram2D>("v2pT_3_chkaons", EdgesC[centrality_type], EdgesMom["v2pT:2:K+_K-"], EdgesRap["v2pT:2:K+_K-"]);
    Histograms2D["v2pT_3_charged"] = std::make_unique<Histogram2D>("v2pT_3_charged", EdgesC[centrality_type], EdgesMom["v2pT:2:charged"], EdgesRap["v2pT:2:charged"]);
    // Histograms2D["v3pT_3_chprotons"] = std::make_unique<Histogram2D>("v3pT_3_chprotons", EdgesC[centrality_type], EdgesMom["v2pT:2:p_pbar"], EdgesRap["v2pT:2:p_pbar"]);
    // Histograms2D["v3pT_3_chpions"] = std::make_unique<Histogram2D>("v3pT_3_chpions", EdgesC[centrality_type], EdgesMom["v2pT:2:pi+_pi-"], EdgesRap["v2pT:2:pi+_pi-"]);
    // Histograms2D["v3pT_3_chkaons"] = std::make_unique<Histogram2D>("v3pT_3_chkaons", EdgesC[centrality_type], EdgesMom["v2pT:2:K+_K-"], EdgesRap["v2pT:2:K+_K-"]);
    // Histograms2D["v3pT_3_charged"] = std::make_unique<Histogram2D>("v3pT_3_charged", EdgesC[centrality_type], EdgesMom["v2pT:2:charged"], EdgesRap["v2pT:2:charged"]);
    // Histograms2D["v4pT_3_chprotons"] = std::make_unique<Histogram2D>("v4pT_3_chprotons", EdgesC[centrality_type], EdgesMom["v2pT:2:p_pbar"], EdgesRap["v2pT:2:p_pbar"]);
    // Histograms2D["v4pT_3_chpions"] = std::make_unique<Histogram2D>("v4pT_3_chpions", EdgesC[centrality_type], EdgesMom["v2pT:2:pi+_pi-"], EdgesRap["v2pT:2:pi+_pi-"]);
    // Histograms2D["v4pT_3_chkaons"] = std::make_unique<Histogram2D>("v4pT_3_chkaons", EdgesC[centrality_type], EdgesMom["v2pT:2:K+_K-"], EdgesRap["v2pT:2:K+_K-"]);
    // Histograms2D["v4pT_3_charged"] = std::make_unique<Histogram2D>("v4pT_3_charged", EdgesC[centrality_type], EdgesMom["v2pT:2:charged"], EdgesRap["v2pT:2:charged"]);
    // Histograms2D["v5pT_3_chprotons"] = std::make_unique<Histogram2D>("v5pT_3_chprotons", EdgesC[centrality_type], EdgesMom["v2pT:2:p_pbar"], EdgesRap["v2pT:2:p_pbar"]);
    // Histograms2D["v5pT_3_chpions"] = std::make_unique<Histogram2D>("v5pT_3_chpions", EdgesC[centrality_type], EdgesMom["v2pT:2:pi+_pi-"], EdgesRap["v2pT:2:pi+_pi-"]);
    // Histograms2D["v5pT_3_chkaons"] = std::make_unique<Histogram2D>("v5pT_3_chkaons", EdgesC[centrality_type], EdgesMom["v2pT:2:K+_K-"], EdgesRap["v2pT:2:K+_K-"]);
    // Histograms2D["v5pT_3_charged"] = std::make_unique<Histogram2D>("v5pT_3_charged", EdgesC[centrality_type], EdgesMom["v2pT:2:charged"], EdgesRap["v2pT:2:charged"]);

    // Average anisotropic flow as function of centrality for low pT and mid rapidity
    EdgesRap["6:p_pbar"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["6:p_pbar"] = (std::vector<double>){0.2, 2.5};
    EdgesRap["6:K+_K-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["6:K+_K-"] = (std::vector<double>){0.2, 2.5};
    EdgesRap["6:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["6:pi+_pi-"] = (std::vector<double>){0.2, 2.5};
    EdgesRap["6:charged"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["6:charged"] = (std::vector<double>){0.2, 2.5};

    Histograms1D["v2_1_chprotons"] = std::make_unique<Histogram1D>("v2_1_chprotons", EdgesC[centrality_type], EdgesMom["6:p_pbar"], EdgesRap["6:p_pbar"]);
    Histograms1D["v2_1_chpions"] = std::make_unique<Histogram1D>("v2_1_chpions", EdgesC[centrality_type], EdgesMom["6:pi+_pi-"], EdgesRap["6:pi+_pi-"]);
    Histograms1D["v2_1_chkaons"] = std::make_unique<Histogram1D>("v2_1_chkaons", EdgesC[centrality_type], EdgesMom["6:K+_K-"], EdgesRap["6:K+_K-"]);
    Histograms1D["v2_1_charged"] = std::make_unique<Histogram1D>("v2_1_charged", EdgesC[centrality_type], EdgesMom["6:charged"], EdgesRap["6:charged"]);

    // Histograms1D["v3_1_chprotons"] = std::make_unique<Histogram1D>("v3_1_chprotons", EdgesC[centrality_type], EdgesMom["6:p_pbar"], EdgesRap["6:p_pbar"]);
    // Histograms1D["v3_1_chpions"] = std::make_unique<Histogram1D>("v3_1_chpions", EdgesC[centrality_type], EdgesMom["6:pi+_pi-"], EdgesRap["6:pi+_pi-"]);
    // Histograms1D["v3_1_chkaons"] = std::make_unique<Histogram1D>("v3_1_chkaons", EdgesC[centrality_type], EdgesMom["6:K+_K-"], EdgesRap["6:K+_K-"]);
    // Histograms1D["v3_1_charged"] = std::make_unique<Histogram1D>("v3_1_charged", EdgesC[centrality_type], EdgesMom["6:charged"], EdgesRap["6:charged"]);

    // Histograms1D["v4_1_chprotons"] = std::make_unique<Histogram1D>("v4_1_chprotons", EdgesC[centrality_type], EdgesMom["6:p_pbar"], EdgesRap["6:p_pbar"]);
    // Histograms1D["v4_1_chpions"] = std::make_unique<Histogram1D>("v4_1_chpions", EdgesC[centrality_type], EdgesMom["6:pi+_pi-"], EdgesRap["6:pi+_pi-"]);
    // Histograms1D["v4_1_chkaons"] = std::make_unique<Histogram1D>("v4_1_chkaons", EdgesC[centrality_type], EdgesMom["6:K+_K-"], EdgesRap["6:K+_K-"]);
    // Histograms1D["v4_1_charged"] = std::make_unique<Histogram1D>("v4_1_charged", EdgesC[centrality_type], EdgesMom["6:charged"], EdgesRap["6:charged"]);

    // Histograms1D["v5_1_chprotons"] = std::make_unique<Histogram1D>("v5_1_chprotons", EdgesC[centrality_type], EdgesMom["6:p_pbar"], EdgesRap["6:p_pbar"]);
    // Histograms1D["v5_1_chpions"] = std::make_unique<Histogram1D>("v5_1_chpions", EdgesC[centrality_type], EdgesMom["6:pi+_pi-"], EdgesRap["6:pi+_pi-"]);
    // Histograms1D["v5_1_chkaons"] = std::make_unique<Histogram1D>("v5_1_chkaons", EdgesC[centrality_type], EdgesMom["6:K+_K-"], EdgesRap["6:K+_K-"]);
    // Histograms1D["v5_1_charged"] = std::make_unique<Histogram1D>("v5_1_charged", EdgesC[centrality_type], EdgesMom["6:charged"], EdgesRap["6:charged"]);

    Histograms1D["v2_2_chprotons"] = std::make_unique<Histogram1D>("v2_2_chprotons", EdgesC[centrality_type], EdgesMom["6:p_pbar"], EdgesRap["6:p_pbar"]);
    Histograms1D["v2_2_chpions"] = std::make_unique<Histogram1D>("v2_2_chpions", EdgesC[centrality_type], EdgesMom["6:pi+_pi-"], EdgesRap["6:pi+_pi-"]);
    Histograms1D["v2_2_chkaons"] = std::make_unique<Histogram1D>("v2_2_chkaons", EdgesC[centrality_type], EdgesMom["6:K+_K-"], EdgesRap["6:K+_K-"]);
    Histograms1D["v2_2_charged"] = std::make_unique<Histogram1D>("v2_2_charged", EdgesC[centrality_type], EdgesMom["6:charged"], EdgesRap["6:charged"]);

    // Histograms1D["v3_2_chprotons"] = std::make_unique<Histogram1D>("v3_2_chprotons", EdgesC[centrality_type], EdgesMom["6:p_pbar"], EdgesRap["6:p_pbar"]);
    // Histograms1D["v3_2_chpions"] = std::make_unique<Histogram1D>("v3_2_chpions", EdgesC[centrality_type], EdgesMom["6:pi+_pi-"], EdgesRap["6:pi+_pi-"]);
    // Histograms1D["v3_2_chkaons"] = std::make_unique<Histogram1D>("v3_2_chkaons", EdgesC[centrality_type], EdgesMom["6:K+_K-"], EdgesRap["6:K+_K-"]);
    // Histograms1D["v3_2_charged"] = std::make_unique<Histogram1D>("v3_2_charged", EdgesC[centrality_type], EdgesMom["6:charged"], EdgesRap["6:charged"]);

    // Histograms1D["v4_2_chprotons"] = std::make_unique<Histogram1D>("v4_2_chprotons", EdgesC[centrality_type], EdgesMom["6:p_pbar"], EdgesRap["6:p_pbar"]);
    // Histograms1D["v4_2_chpions"] = std::make_unique<Histogram1D>("v4_2_chpions", EdgesC[centrality_type], EdgesMom["6:pi+_pi-"], EdgesRap["6:pi+_pi-"]);
    // Histograms1D["v4_2_chkaons"] = std::make_unique<Histogram1D>("v4_2_chkaons", EdgesC[centrality_type], EdgesMom["6:K+_K-"], EdgesRap["6:K+_K-"]);
    // Histograms1D["v4_2_charged"] = std::make_unique<Histogram1D>("v4_2_charged", EdgesC[centrality_type], EdgesMom["6:charged"], EdgesRap["6:charged"]);

    // Histograms1D["v5_2_chprotons"] = std::make_unique<Histogram1D>("v5_2_chprotons", EdgesC[centrality_type], EdgesMom["6:p_pbar"], EdgesRap["6:p_pbar"]);
    // Histograms1D["v5_2_chpions"] = std::make_unique<Histogram1D>("v5_2_chpions", EdgesC[centrality_type], EdgesMom["6:pi+_pi-"], EdgesRap["6:pi+_pi-"]);
    // Histograms1D["v5_2_chkaons"] = std::make_unique<Histogram1D>("v5_2_chkaons", EdgesC[centrality_type], EdgesMom["6:K+_K-"], EdgesRap["6:K+_K-"]);
    // Histograms1D["v5_2_charged"] = std::make_unique<Histogram1D>("v5_2_charged", EdgesC[centrality_type], EdgesMom["6:charged"], EdgesRap["6:charged"]);

    // Histograms for THERMAL-FIST
    EdgesRap["1:thermalfist"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:thermalfist"] = (std::vector<double>){0.1, 2.};
    HistogramMaps3D["yield_1_map"] = std::make_unique<HistogramMap3D>("yield_1_map", EdgesC[centrality_type], EdgesMom["1:thermalfist"], EdgesRap["1:thermalfist"]);
};

void DataContainer::AddParticle(Statistics::Block &block, Statistics::Line &line) {
    if (line.GetParticlePythiaID() == 211 | line.GetParticlePythiaID() == -211) {
        Histograms2D["dNdptdy_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);

        Histograms2D["dNdptdeta_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);

        Histograms1D["meanpt_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());
        Histograms1D["meanpt_3_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), line.GetTransverseMomentum());
        Histograms1D["meanpt_2_chpions"]->Add((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());

        Histograms1D["meanyield_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms1D["meanyieldeta_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);
        Histograms1D["meanyield_2_chpions"]->AddCurrent(block.GetNumberOfChargedParticles(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms1D["meanyield_3_chpions"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);

        Histograms2D["dNdy_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetRapidity(), line.GetTransverseMomentum(), 1.0);
        Histograms2D["dNdy_2_chpions"]->AddCurrent((block.*funcptr)(), line.GetRapidity(), line.GetTransverseMomentum(), 1.0);

        Histograms2D["dNdeta_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetPseudoRapidity(), line.GetTransverseMomentum(), 1.0);
        Histograms2D["dNdeta_2_chpions"]->AddCurrent((block.*funcptr)(), line.GetPseudoRapidity(), line.GetTransverseMomentum(), 1.0);

        Histograms2D["v2pT_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms2D["v2pT_2_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms2D["v2pT_3_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlowOld(2));
        // Histograms2D["v3pT_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms2D["v3pT_2_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms2D["v4pT_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms2D["v4pT_2_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms2D["v5pT_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        // Histograms2D["v5pT_2_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));

        Histograms1D["v2_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms1D["v2_2_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlowOld(2));
        // Histograms1D["v3_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms1D["v4_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms1D["v5_1_chpions"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
    } else if (line.GetParticlePythiaID() == 321 | line.GetParticlePythiaID() == -321) {
        Histograms2D["dNdptdy_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);

        Histograms2D["dNdptdeta_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);

        Histograms1D["meanpt_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());
        Histograms1D["meanpt_3_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), line.GetTransverseMomentum());
        Histograms1D["meanpt_2_chkaons"]->Add((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());

        Histograms1D["meanyield_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms1D["meanyieldeta_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);
        Histograms1D["meanyield_2_chkaons"]->AddCurrent(block.GetNumberOfChargedParticles(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms1D["meanyield_3_chkaons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);

        Histograms2D["dNdy_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetRapidity(), line.GetTransverseMomentum(), 1.0);
        Histograms2D["dNdy_2_chkaons"]->AddCurrent((block.*funcptr)(), line.GetRapidity(), line.GetTransverseMomentum(), 1.0);

        Histograms2D["dNdeta_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetPseudoRapidity(), line.GetTransverseMomentum(), 1.0);
        Histograms2D["dNdeta_2_chkaons"]->AddCurrent((block.*funcptr)(), line.GetPseudoRapidity(), line.GetTransverseMomentum(), 1.0);

        Histograms2D["v2pT_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms2D["v2pT_2_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms2D["v2pT_3_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlowOld(2));
        // Histograms2D["v3pT_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms2D["v3pT_2_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms2D["v4pT_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms2D["v4pT_2_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms2D["v5pT_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        // Histograms2D["v5pT_2_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));

        Histograms1D["v2_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms1D["v2_2_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlowOld(2));
        // Histograms1D["v3_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms1D["v4_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms1D["v5_1_chkaons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
    } else if (line.GetParticlePythiaID() == 2212 | line.GetParticlePythiaID() == -2212) {
        Histograms2D["dNdptdy_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);

        Histograms2D["dNdptdeta_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);

        Histograms1D["meanpt_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());
        Histograms1D["meanpt_3_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), line.GetTransverseMomentum());
        Histograms1D["meanpt_2_chprotons"]->Add((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());

        Histograms1D["meanyield_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms1D["meanyieldeta_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);
        Histograms1D["meanyield_2_chprotons"]->AddCurrent(block.GetNumberOfChargedParticles(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms1D["meanyield_3_chprotons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);

        Histograms2D["dNdy_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetRapidity(), line.GetTransverseMomentum(), 1.0);
        Histograms2D["dNdy_2_chprotons"]->AddCurrent((block.*funcptr)(), line.GetRapidity(), line.GetTransverseMomentum(), 1.0);

        Histograms2D["dNdeta_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetPseudoRapidity(), line.GetTransverseMomentum(), 1.0);
        Histograms2D["dNdeta_2_chprotons"]->AddCurrent((block.*funcptr)(), line.GetPseudoRapidity(), line.GetTransverseMomentum(), 1.0);

        Histograms2D["v2pT_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms2D["v2pT_2_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms2D["v2pT_3_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlowOld(2));
        // Histograms2D["v3pT_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms2D["v3pT_2_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms2D["v4pT_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms2D["v4pT_2_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms2D["v5pT_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        // Histograms2D["v5pT_2_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));

        Histograms1D["v2_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms1D["v2_2_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlowOld(2));
        // Histograms1D["v3_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms1D["v4_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms1D["v5_1_chprotons"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
    }
    if (ChargeMap[line.GetParticlePythiaID()] != 0) {
        Histograms2D["dNdptdy_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);

        Histograms2D["dNdptdeta_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);

        Histograms1D["meanpt_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());
        Histograms1D["meanpt_3_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), line.GetTransverseMomentum());
        Histograms1D["meanpt_2_charged"]->Add((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());

        Histograms1D["meanyield_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms1D["meanyieldeta_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);
        Histograms1D["meanyield_2_charged"]->AddCurrent(block.GetNumberOfChargedParticles(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms1D["meanyield_3_charged"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);

        Histograms2D["dNdy_1_charged"]->AddCurrent((block.*funcptr)(), line.GetRapidity(), line.GetTransverseMomentum(), 1.0);
        Histograms2D["dNdy_2_charged"]->AddCurrent((block.*funcptr)(), line.GetRapidity(), line.GetTransverseMomentum(), 1.0);

        Histograms2D["dNdeta_1_charged"]->AddCurrent((block.*funcptr)(), line.GetPseudoRapidity(), line.GetTransverseMomentum(), 1.0);
        Histograms2D["dNdeta_2_charged"]->AddCurrent((block.*funcptr)(), line.GetPseudoRapidity(), line.GetTransverseMomentum(), 1.0);

        Histograms2D["v2pT_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms2D["v2pT_2_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms2D["v2pT_3_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlowOld(2));
        // Histograms2D["v3pT_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms2D["v3pT_2_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms2D["v4pT_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms2D["v4pT_2_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms2D["v5pT_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        // Histograms2D["v5pT_2_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));

        Histograms1D["v2_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms1D["v2_2_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlowOld(2));
        // Histograms1D["v3_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        // Histograms1D["v4_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        // Histograms1D["v5_1_charged"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
    }
    HistogramMaps3D["yield_1_map"]->AddCurrent((block.*funcptr)(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetParticlePythiaID(), 1.0);
};

void DataContainer::AddEvent(Statistics::Block &block) {
    Histograms1D["impactparameter_1"]->Add((block.*funcptr)(), block.GetImpactParameter());
    Histograms1D["participation_1"]->Add((block.*funcptr)(), block.GetNumberOfParticipantNucleons());
    Histograms1D["binarycollisions_1"]->Add((block.*funcptr)(), block.GetNumberOfBinaryCollisions());

    Histograms1D["impactparameter_2"]->Add(block.GetNumberOfChargedParticles(), block.GetImpactParameter());
    Histograms1D["participation_2"]->Add(block.GetNumberOfChargedParticles(), block.GetNumberOfParticipantNucleons());
    Histograms1D["binarycollisions_2"]->Add(block.GetNumberOfChargedParticles(), block.GetNumberOfBinaryCollisions());

    HistogramMaps3D["yield_1_map"]->AddEvent();

    Histograms2D["dNdptdy_1_chpions"]->AddEvent();

    Histograms2D["dNdptdeta_1_chpions"]->AddEvent();

    Histograms1D["meanpt_1_chpions"]->AddEventAverage();

    Histograms1D["meanyield_1_chpions"]->AddEvent();
    Histograms1D["meanyieldeta_1_chpions"]->AddEvent();
    Histograms1D["meanyield_3_chpions"]->AddEvent();
    Histograms1D["meanyield_2_chpions"]->AddEvent();
    Histograms2D["dNdy_2_chpions"]->AddEvent();
    Histograms2D["dNdy_1_chpions"]->AddEvent();
    Histograms2D["dNdeta_2_chpions"]->AddEvent();
    Histograms2D["dNdeta_1_chpions"]->AddEvent();
    // Histograms2D["v3pT_1_chpions"]->AddEventAverage();
    // Histograms2D["v3pT_2_chpions"]->AddEventAverage();
    Histograms2D["v2pT_1_chpions"]->AddEventAverage();
    Histograms2D["v2pT_2_chpions"]->AddEventAverage();
    Histograms2D["v2pT_3_chpions"]->AddEventAverage();
    // Histograms2D["v5pT_1_chpions"]->AddEventAverage();
    // Histograms2D["v5pT_2_chpions"]->AddEventAverage();
    // Histograms2D["v4pT_1_chpions"]->AddEventAverage();
    // Histograms2D["v4pT_2_chpions"]->AddEventAverage();
    // Histograms1D["v3_1_chpions"]->AddEventAverage();
    Histograms1D["v2_1_chpions"]->AddEventAverage();
    Histograms1D["v2_2_chpions"]->AddEventAverage();
    // Histograms1D["v5_1_chpions"]->AddEventAverage();
    // Histograms1D["v4_1_chpions"]->AddEventAverage();
    Histograms2D["dNdptdeta_1_chkaons"]->AddEvent();
    Histograms2D["dNdptdy_1_chkaons"]->AddEvent();
    Histograms1D["meanyield_1_chkaons"]->AddEvent();
    Histograms1D["meanyieldeta_1_chkaons"]->AddEvent();
    Histograms1D["meanpt_1_chkaons"]->AddEventAverage();
    Histograms1D["meanyield_3_chkaons"]->AddEvent();
    Histograms1D["meanyield_2_chkaons"]->AddEvent();
    Histograms2D["dNdy_2_chkaons"]->AddEvent();
    Histograms2D["dNdy_1_chkaons"]->AddEvent();
    Histograms2D["dNdeta_2_chkaons"]->AddEvent();
    Histograms2D["dNdeta_1_chkaons"]->AddEvent();
    // Histograms2D["v3pT_1_chkaons"]->AddEventAverage();
    // Histograms2D["v3pT_2_chkaons"]->AddEventAverage();
    Histograms2D["v2pT_1_chkaons"]->AddEventAverage();
    Histograms2D["v2pT_2_chkaons"]->AddEventAverage();
    Histograms2D["v2pT_3_chkaons"]->AddEventAverage();
    // Histograms2D["v5pT_1_chkaons"]->AddEventAverage();
    // Histograms2D["v5pT_2_chkaons"]->AddEventAverage();
    // Histograms2D["v4pT_1_chkaons"]->AddEventAverage();
    // Histograms2D["v4pT_2_chkaons"]->AddEventAverage();
    // Histograms1D["v3_1_chkaons"]->AddEventAverage();
    Histograms1D["v2_1_chkaons"]->AddEventAverage();
    Histograms1D["v2_2_chkaons"]->AddEventAverage();
    // Histograms1D["v5_1_chkaons"]->AddEventAverage();
    // Histograms1D["v4_1_chkaons"]->AddEventAverage();
    Histograms2D["dNdptdeta_1_chprotons"]->AddEvent();
    Histograms2D["dNdptdy_1_chprotons"]->AddEvent();
    Histograms1D["meanyield_1_chprotons"]->AddEvent();
    Histograms1D["meanyieldeta_1_chprotons"]->AddEvent();
    Histograms1D["meanpt_1_chprotons"]->AddEventAverage();
    Histograms1D["meanyield_3_chprotons"]->AddEvent();
    Histograms1D["meanyield_2_chprotons"]->AddEvent();
    Histograms2D["dNdy_2_chprotons"]->AddEvent();
    Histograms2D["dNdy_1_chprotons"]->AddEvent();
    Histograms2D["dNdeta_2_chprotons"]->AddEvent();
    Histograms2D["dNdeta_1_chprotons"]->AddEvent();
    // Histograms2D["v3pT_1_chprotons"]->AddEventAverage();
    // Histograms2D["v3pT_2_chprotons"]->AddEventAverage();
    Histograms2D["v2pT_1_chprotons"]->AddEventAverage();
    Histograms2D["v2pT_2_chprotons"]->AddEventAverage();
    Histograms2D["v2pT_3_chprotons"]->AddEventAverage();
    // Histograms2D["v5pT_1_chprotons"]->AddEventAverage();
    // Histograms2D["v5pT_2_chprotons"]->AddEventAverage();
    // Histograms2D["v4pT_1_chprotons"]->AddEventAverage();
    // Histograms2D["v4pT_2_chprotons"]->AddEventAverage();
    // Histograms1D["v3_1_chprotons"]->AddEventAverage();
    Histograms1D["v2_1_chprotons"]->AddEventAverage();
    Histograms1D["v2_2_chprotons"]->AddEventAverage();
    // Histograms1D["v5_1_chprotons"]->AddEventAverage();
    // Histograms1D["v4_1_chprotons"]->AddEventAverage();
    Histograms2D["dNdptdeta_1_charged"]->AddEvent();
    Histograms2D["dNdptdy_1_charged"]->AddEvent();
    Histograms1D["meanyield_1_charged"]->AddEvent();
    Histograms1D["meanyieldeta_1_charged"]->AddEvent();
    Histograms1D["meanpt_1_charged"]->AddEventAverage();
    Histograms1D["meanyield_3_charged"]->AddEvent();
    Histograms1D["meanyield_2_charged"]->AddEvent();
    Histograms2D["dNdy_2_charged"]->AddEvent();
    Histograms2D["dNdy_1_charged"]->AddEvent();
    Histograms2D["dNdeta_2_charged"]->AddEvent();
    Histograms2D["dNdeta_1_charged"]->AddEvent();
    // Histograms2D["v3pT_1_charged"]->AddEventAverage();
    // Histograms2D["v3pT_2_charged"]->AddEventAverage();
    Histograms2D["v2pT_1_charged"]->AddEventAverage();
    Histograms2D["v2pT_2_charged"]->AddEventAverage();
    Histograms2D["v2pT_3_charged"]->AddEventAverage();
    // Histograms2D["v5pT_1_charged"]->AddEventAverage();
    // Histograms2D["v5pT_2_charged"]->AddEventAverage();
    // Histograms2D["v4pT_1_charged"]->AddEventAverage();
    // Histograms2D["v4pT_2_charged"]->AddEventAverage();
    // Histograms1D["v3_1_charged"]->AddEventAverage();
    Histograms1D["v2_1_charged"]->AddEventAverage();
    Histograms1D["v2_2_charged"]->AddEventAverage();
    // Histograms1D["v5_1_charged"]->AddEventAverage();
    // Histograms1D["v4_1_charged"]->AddEventAverage();
};

void DataContainer::AddEventBlock(std::shared_ptr<Statistics::Block> block) {
    EventBlocks.push_back(std::move(block));
    NumberOfBlocks++;
}

void DataContainer::CalculateCentralityClasses() {
    std::vector<double> ncharged;
    for (auto entry : EventBlocks) {
        ncharged.push_back(entry->GetNumberOfChargedParticles());
    }
    // std::cout << "ihello" << std::endl;
    std::sort(ncharged.begin(), ncharged.end());
    // std::cout << "ihello" << std::endl;
    std::vector<int> centrality_cut_list = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    std::vector<double> temp(centrality_cut_list.size(), 0);
    for (size_t icen = 0; icen < centrality_cut_list.size() - 1; ++icen) {
        int lower_percentile = centrality_cut_list[icen];
        int upper_percentile = centrality_cut_list[icen + 1];

        // Calculate the lower and upper values for the specified percentiles
        size_t lower_index = static_cast<size_t>(ncharged.size() * lower_percentile / 100);
        size_t upper_index = static_cast<size_t>(ncharged.size() * upper_percentile / 100);

        int dN_dy_cut_low = ncharged[lower_index];
        int dN_dy_cut_high = ncharged[upper_index - 1];
        temp[icen + 1] = (double)dN_dy_cut_high;
    }
    // std::cout << "ihello" << std::endl;
    std::reverse(temp.begin(), temp.end());
    EdgesC["ncharged"] = temp;

    // for (int i = 0; i < temp.size(); ++i) {
    //     EdgesC["ncharged"].push_back(temp[i]);
    // }
}

};  // namespace Statistics
