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
    if (collisiontype == 0) {
        centrality_type = "1:PbPb5020";
    } else if (collisiontype == 1) {
        centrality_type = "1:pPb5020";
    } else if (collisiontype == 2) {
        centrality_type = "1:pp5020";
    } else {
        centrality_type = "1:PbPb5020";
    }
}

void DataContainer::WriteData(std::string DataDirectory) {
    std::stringstream Filename;
    std::ofstream File;
    double Filesize;

    for (const auto &entry : Histograms3D) {
        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "COUNT"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms3D[entry.first]->PrintCount(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 1);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fKB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "TOTAL"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms3D[entry.first]->PrintTotal(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 1);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fKB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "TOTALSQR"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms3D[entry.first]->PrintTotalSQR(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 1);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fKB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "SETTINGS"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms3D[entry.first]->PrintEdges(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 1);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fKB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();
    }
    for (const auto &entry : Histograms1D) {
        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "COUNT"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms1D[entry.first]->PrintCount(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 1);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fKB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "TOTAL"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms1D[entry.first]->PrintTotal(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 1);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fKB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "TOTALSQR"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms1D[entry.first]->PrintTotalSQR(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 1);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fKB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "SETTINGS"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        Histograms1D[entry.first]->PrintEdges(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 1);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fKB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();
    }
    for (const auto &entry : HistogramMaps3D) {
        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "COUNT"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        HistogramMaps3D[entry.first]->PrintCount(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 2);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "TOTAL"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        HistogramMaps3D[entry.first]->PrintTotal(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 2);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "TOTALSQR"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        HistogramMaps3D[entry.first]->PrintTotalSQR(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 2);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
        Filename.str("");
        Filename.clear();

        Filename << DataDirectory << "/" << Filenames[entry.first] << "_"
                 << "SETTINGS"
                 << "." << DEFAULT_EXTENSION_HISTOGRAM;
        File.open(Filename.str(), std::ios::out);
        HistogramMaps3D[entry.first]->PrintEdges(File);
        File.close();
        Filesize = Utilities::GetFileSize(Filename.str(), 1);
        printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        printf("%s[%07.3fKB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
        printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
        fflush(stdout);
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
    // std::cout << "iihello" << std::endl;
    for (int i = 0; i < NumberOfBlocks; ++i) {
        // std::cout << "iihello" << std::endl;
        EventBlocks[i]->Write(File);
        // std::cout << "iihello" << std::endl;
        File << "\n";
    }
    // std::cout << "iihello" << std::endl;
    File.close();
    Filesize = Utilities::GetFileSize(Filename.str(), 2);
    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, Filesize, PP::RESET);
    printf("%-14s : %s\n", "Writen data to", Filename.str().c_str());
    fflush(stdout);
    Filename.str("");
    Filename.clear();
};

void DataContainer::Add(DataContainer const &obj) {
    for (const auto &entry : Histograms1D) {
        if (Histograms1D.find(entry.first) != Histograms1D.end() &&
            obj.Histograms1D.find(entry.first) != obj.Histograms1D.end()) {
            // Check if both histograms exist before attempting to add them
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

    for (const auto &entry : Histograms3D) {
        if (Histograms3D.find(entry.first) != Histograms3D.end() &&
            obj.Histograms3D.find(entry.first) != obj.Histograms3D.end()) {
            // Check if both histograms exist before attempting to add them
            *Histograms3D.at(entry.first) += *obj.Histograms3D.at(entry.first);
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
        if (HistogramMaps3D.find(entry.first) != HistogramMaps3D.end() &&
            obj.HistogramMaps3D.find(entry.first) !=
                obj.HistogramMaps3D.end()) {
            // Check if both histograms exist before attempting to add them
            *HistogramMaps3D.at(entry.first) +=
                *obj.HistogramMaps3D.at(entry.first);
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

void DataContainer::InitialiseHistograms() {
    centrality_type = "1:PbPb5020";

    EdgesC["1:PbPb5020"] = (std::vector<double>){0.00, 3.49, 4.93, 6.98, 8.55, 9.87, 11.00, 12.10, 13.10, 14.00, 14.90, 20.00};
    // EdgesC["2:PbPb5020"] = (std::vector<double>){0.00,3.49,4.93,6.04,6.98,7.80,8.55,9.23,9.87,10.50,11.00,11.60,12.10,12.60,13.10,13.50,14.00,14.40,14.90,15.60,20.00};
    EdgesC["1:pPb5020"] = (std::vector<double>){0.00, 1.82, 2.58, 3.65, 4.47, 5.16, 5.77, 6.32, 6.84, 7.36, 7.99, 14.70};
    EdgesC["1:pp5020"] = (std::vector<double>){0.00, 20.00};

    EdgesRap["1:p_pbar"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:p_pbar"] = (std::vector<double>){0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2., 2.2, 2.4, 2.6, 2.8, 3., 3.2, 3.4, 3.6, 3.8, 4., 4.5, 5., 5.5, 6., 6.5, 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 18., 20.};
    EdgesRap["1:K+_K-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:K+_K-"] = (std::vector<double>){0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2., 2.2, 2.4, 2.6, 2.8, 3., 3.2, 3.4, 3.6, 3.8, 4., 4.5, 5., 5.5, 6., 6.5, 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 18., 20.};
    EdgesRap["1:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:pi+_pi-"] = (std::vector<double>){0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2., 2.2, 2.4, 2.6, 2.8, 3., 3.2, 3.4, 3.6, 3.8, 4., 4.5, 5., 5.5, 6., 6.5, 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 18., 20.};
    EdgesRap["1:charged"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:charged"] = (std::vector<double>){0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2., 2.2, 2.4, 2.6, 2.8, 3., 3.2, 3.4, 3.6, 3.8, 4., 4.5, 5., 5.5, 6., 6.5, 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 18., 20.};

    EdgesRap["2:p_pbar"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["2:p_pbar"] = (std::vector<double>){0.5, 1., 1.5, 2., 2.5, 3., 4., 6.};
    EdgesRap["2:K+_K-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["2:K+_K-"] = (std::vector<double>){0.3, 0.6, 1., 1.5, 2., 2.5, 3., 4., 6.};
    EdgesRap["2:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["2:pi+_pi-"] = (std::vector<double>){0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1., 1.25, 1.5, 1.75, 2., 2.25, 2.5, 3., 3.5, 4., 5., 6., 8., 10.};
    EdgesRap["2:charged"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["2:charged"] = (std::vector<double>){0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1., 1.25, 1.5, 1.75, 2., 2.25, 2.5, 3., 3.5, 4., 5., 6., 8., 10.};

    EdgesRap["3:p_pbar"] = (std::vector<double>){-10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
    EdgesMom["3:p_pbar"] = (std::vector<double>){0.01, 20.};
    EdgesRap["3:K+_K-"] = (std::vector<double>){-10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
    EdgesMom["3:K+_K-"] = (std::vector<double>){0.01, 20.};
    EdgesRap["3:pi+_pi-"] = (std::vector<double>){-10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
    EdgesMom["3:pi+_pi-"] = (std::vector<double>){0.01, 20.};
    EdgesRap["3:charged"] = (std::vector<double>){-10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
    EdgesMom["3:charged"] = (std::vector<double>){0.01, 20.};

    EdgesRap["4:p_pbar"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["4:p_pbar"] = (std::vector<double>){0.2, 5.};
    EdgesRap["4:K+_K-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["4:K+_K-"] = (std::vector<double>){0.2, 5.};
    EdgesRap["4:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["4:pi+_pi-"] = (std::vector<double>){0.2, 5.};
    EdgesRap["4:charged"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["4:charged"] = (std::vector<double>){0.2, 5.};

    EdgesRap["5:p_pbar"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["5:p_pbar"] = (std::vector<double>){0.2, 2.};
    EdgesRap["5:K+_K-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["5:K+_K-"] = (std::vector<double>){0.2, 2.};
    EdgesRap["5:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["5:pi+_pi-"] = (std::vector<double>){0.2, 2.};
    EdgesRap["5:charged"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["5:charged"] = (std::vector<double>){0.2, 2.};

    EdgesRap["1:meanpt"] = (std::vector<double>){-0.5, 0.5};
    EdgesMom["1:meanpt"] = (std::vector<double>){0., 3.};

    // EdgesRap["3:pi+_pi-"]  = (std::vector<double>){-0.5, 0.5};
    // EdgesMom["3:pi+_pi-"]  = (std::vector<double>){0.2 ,  0.25,  0.3 ,  0.35,  0.4 ,  0.45,  0.5 ,  0.55,  0.6 , 0.65,  0.7 ,  0.75,  0.8 ,  0.85,  0.9 ,  0.95,  1.  ,  1.1 , 1.2 ,  1.3 ,  1.4 ,  1.5 ,  1.6 ,  1.7 ,  1.8 ,  1.9 ,  2.  , 2.2 ,  2.4 ,  2.6 ,  2.8 ,  3.  ,  3.2 ,  3.4 ,  3.6 ,  3.8 , 4.  ,  4.5 ,  5.  ,  5.5 ,  6.  ,  6.5 ,  7.  ,  8.  ,  9.  , 10.  , 11.  , 12.  , 13.  , 14.  , 15.  , 16.  , 18.  , 20.  };
    // EdgesRap["4:pi+_pi-"]  = (std::vector<double>){-0.5, 0.5};
    // EdgesMom["4:pi+_pi-"]  = (std::vector<double>){0.3 ,  0.35,  0.4 ,  0.45,  0.5 ,  0.55,  0.6 ,  0.65,  0.7 , 0.75,  0.8 ,  0.85,  0.9 ,  0.95,  1.  ,  1.1 ,  1.2 ,  1.3 , 1.4 ,  1.5 ,  1.6 ,  1.7 ,  1.8 ,  1.9 ,  2.  ,  2.2 ,  2.4 , 2.6 ,  2.8 ,  3.  ,  3.2 ,  3.4 ,  3.6 ,  3.8 ,  4.  ,  4.5 , 5.  ,  5.5 ,  6.  ,  6.5 ,  7.  ,  8.  ,  9.  , 10.  , 11.  , 12.  , 13.  , 14.  , 15.  , 16.  , 18.  , 20. };

    // HISTOGRAMS

    Histograms3D["meanpt_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);

    Histograms3D["meanpt_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms3D["meanpt_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms3D["meanpt_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms3D["yield_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms3D["yield_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms3D["yield_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);
    Histograms3D["yield_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:meanpt"], EdgesRap["1:meanpt"]);

    Histograms3D["pt_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:p_pbar"], EdgesRap["1:p_pbar"]);
    Histograms3D["pt_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:K+_K-"], EdgesRap["1:K+_K-"]);
    Histograms3D["pt_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:pi+_pi-"], EdgesRap["1:pi+_pi-"]);
    Histograms3D["pt_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:charged"], EdgesRap["1:charged"]);
    Histograms3D["v2_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:p_pbar"], EdgesRap["2:p_pbar"]);
    Histograms3D["v2_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:K+_K-"], EdgesRap["2:K+_K-"]);
    Histograms3D["v2_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:pi+_pi-"], EdgesRap["2:pi+_pi-"]);
    Histograms3D["v2_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:charged"], EdgesRap["2:charged"]);
    Histograms3D["v3_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:p_pbar"], EdgesRap["2:p_pbar"]);
    Histograms3D["v3_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:K+_K-"], EdgesRap["2:K+_K-"]);
    Histograms3D["v3_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:pi+_pi-"], EdgesRap["2:pi+_pi-"]);
    Histograms3D["v3_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:charged"], EdgesRap["2:charged"]);
    Histograms3D["v4_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:p_pbar"], EdgesRap["2:p_pbar"]);
    Histograms3D["v4_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:K+_K-"], EdgesRap["2:K+_K-"]);
    Histograms3D["v4_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:pi+_pi-"], EdgesRap["2:pi+_pi-"]);
    Histograms3D["v4_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:charged"], EdgesRap["2:charged"]);
    Histograms3D["v5_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:p_pbar"], EdgesRap["2:p_pbar"]);
    Histograms3D["v5_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:K+_K-"], EdgesRap["2:K+_K-"]);
    Histograms3D["v5_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:pi+_pi-"], EdgesRap["2:pi+_pi-"]);
    Histograms3D["v5_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["2:charged"], EdgesRap["2:charged"]);
    Histograms3D["pt_ratio_chpions_to_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:K+_K-"], EdgesRap["1:K+_K-"]);
    Histograms3D["pt_ratio_chpions_to_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["1:p_pbar"], EdgesRap["1:p_pbar"]);
    Histograms3D["rap_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["3:p_pbar"], EdgesRap["3:p_pbar"]);
    Histograms3D["rap_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["3:K+_K-"], EdgesRap["3:K+_K-"]);
    Histograms3D["rap_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["3:pi+_pi-"], EdgesRap["3:pi+_pi-"]);
    Histograms3D["rap_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["3:charged"], EdgesRap["3:charged"]);
    Histograms3D["psrap_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["3:p_pbar"], EdgesRap["3:p_pbar"]);
    Histograms3D["psrap_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["3:K+_K-"], EdgesRap["3:K+_K-"]);
    Histograms3D["psrap_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["3:pi+_pi-"], EdgesRap["3:pi+_pi-"]);
    Histograms3D["psrap_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["3:charged"], EdgesRap["3:charged"]);

    Histograms3D["v2_2_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:p_pbar"], EdgesRap["4:p_pbar"]);
    Histograms3D["v2_2_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:K+_K-"], EdgesRap["4:K+_K-"]);
    Histograms3D["v2_2_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:pi+_pi-"], EdgesRap["4:pi+_pi-"]);
    Histograms3D["v2_2_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:charged"], EdgesRap["4:charged"]);
    Histograms3D["v3_2_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:p_pbar"], EdgesRap["4:p_pbar"]);
    Histograms3D["v3_2_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:K+_K-"], EdgesRap["4:K+_K-"]);
    Histograms3D["v3_2_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:pi+_pi-"], EdgesRap["4:pi+_pi-"]);
    Histograms3D["v3_2_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:charged"], EdgesRap["4:charged"]);
    Histograms3D["v4_2_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:p_pbar"], EdgesRap["4:p_pbar"]);
    Histograms3D["v4_2_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:K+_K-"], EdgesRap["4:K+_K-"]);
    Histograms3D["v4_2_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:pi+_pi-"], EdgesRap["4:pi+_pi-"]);
    Histograms3D["v4_2_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:charged"], EdgesRap["4:charged"]);
    Histograms3D["v5_2_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:p_pbar"], EdgesRap["4:p_pbar"]);
    Histograms3D["v5_2_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:K+_K-"], EdgesRap["4:K+_K-"]);
    Histograms3D["v5_2_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:pi+_pi-"], EdgesRap["4:pi+_pi-"]);
    Histograms3D["v5_2_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["4:charged"], EdgesRap["4:charged"]);
    Histograms3D["v2_3_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:p_pbar"], EdgesRap["5:p_pbar"]);
    Histograms3D["v2_3_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:K+_K-"], EdgesRap["5:K+_K-"]);
    Histograms3D["v2_3_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:pi+_pi-"], EdgesRap["5:pi+_pi-"]);
    Histograms3D["v2_3_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:charged"], EdgesRap["5:charged"]);
    Histograms3D["v3_3_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:p_pbar"], EdgesRap["5:p_pbar"]);
    Histograms3D["v3_3_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:K+_K-"], EdgesRap["5:K+_K-"]);
    Histograms3D["v3_3_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:pi+_pi-"], EdgesRap["5:pi+_pi-"]);
    Histograms3D["v3_3_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:charged"], EdgesRap["5:charged"]);
    Histograms3D["v4_3_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:p_pbar"], EdgesRap["5:p_pbar"]);
    Histograms3D["v4_3_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:K+_K-"], EdgesRap["5:K+_K-"]);
    Histograms3D["v4_3_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:pi+_pi-"], EdgesRap["5:pi+_pi-"]);
    Histograms3D["v4_3_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:charged"], EdgesRap["5:charged"]);
    Histograms3D["v5_3_chprotons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:p_pbar"], EdgesRap["5:p_pbar"]);
    Histograms3D["v5_3_chkaons"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:K+_K-"], EdgesRap["5:K+_K-"]);
    Histograms3D["v5_3_chpions"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:pi+_pi-"], EdgesRap["5:pi+_pi-"]);
    Histograms3D["v5_3_charged"] = std::make_unique<Histogram3D>(EdgesC[centrality_type], EdgesMom["5:charged"], EdgesRap["5:charged"]);

    Histograms1D["impactparameter"] = std::make_unique<Histogram1D>(EdgesC[centrality_type]);
    Histograms1D["participation"] = std::make_unique<Histogram1D>(EdgesC[centrality_type]);
    // Histograms1D["participation_2"]   = std::make_unique<Histogram1D>(EdgesC["2:PbPb5020"]);

    Filenames["meanpt_chprotons"] = "meanpt_chprotons";
    Filenames["meanpt_chkaons"] = "meanpt_chkaons";
    Filenames["meanpt_chpions"] = "meanpt_chpions";
    Filenames["meanpt_charged"] = "meanpt_charged";
    Filenames["yield_chprotons"] = "yield_chprotons";
    Filenames["yield_chkaons"] = "yield_chkaons";
    Filenames["yield_chpions"] = "yield_chpions";
    Filenames["yield_charged"] = "yield_charged";

    Filenames["pt_chprotons"] = "pt_chprotons";
    Filenames["pt_chkaons"] = "pt_chkaons";
    Filenames["pt_chpions"] = "pt_chpions";
    Filenames["pt_charged"] = "pt_charged";
    Filenames["v2_chprotons"] = "v2_chprotons";
    Filenames["v2_chkaons"] = "v2_chkaons";
    Filenames["v2_chpions"] = "v2_chpions";
    Filenames["v2_charged"] = "v2_charged";
    Filenames["v3_chprotons"] = "v3_chprotons";
    Filenames["v3_chkaons"] = "v3_chkaons";
    Filenames["v3_chpions"] = "v3_chpions";
    Filenames["v3_charged"] = "v3_charged";
    Filenames["v4_chprotons"] = "v4_chprotons";
    Filenames["v4_chkaons"] = "v4_chkaons";
    Filenames["v4_chpions"] = "v4_chpions";
    Filenames["v4_charged"] = "v4_charged";
    Filenames["v5_chprotons"] = "v5_chprotons";
    Filenames["v5_chkaons"] = "v5_chkaons";
    Filenames["v5_chpions"] = "v5_chpions";
    Filenames["v5_charged"] = "v5_charged";
    Filenames["pt_ratio_chpions_to_chkaons"] = "pt_ratio_chpions_to_chkaons";
    Filenames["pt_ratio_chpions_to_chprotons"] = "pt_ratio_chpions_to_chprotons";

    Filenames["impactparameter"] = "impactparameter";
    Filenames["participation"] = "participation";
    // Filenames["participation_2"]    = "participation_2";

    Filenames["rap_chprotons"] = "rap_chprotons";
    Filenames["rap_chkaons"] = "rap_chkaons";
    Filenames["rap_chpions"] = "rap_chpions";
    Filenames["rap_charged"] = "rap_charged";
    Filenames["psrap_chprotons"] = "psrap_chprotons";
    Filenames["psrap_chkaons"] = "psrap_chkaons";
    Filenames["psrap_chpions"] = "psrap_chpions";
    Filenames["psrap_charged"] = "psrap_charged";
    Filenames["v2_2_chprotons"] = "v2_2_chprotons";
    Filenames["v2_2_chkaons"] = "v2_2_chkaons";
    Filenames["v2_2_chpions"] = "v2_2_chpions";
    Filenames["v2_2_charged"] = "v2_2_charged";
    Filenames["v3_2_chprotons"] = "v3_2_chprotons";
    Filenames["v3_2_chkaons"] = "v3_2_chkaons";
    Filenames["v3_2_chpions"] = "v3_2_chpions";
    Filenames["v3_2_charged"] = "v3_2_charged";
    Filenames["v4_2_chprotons"] = "v4_2_chprotons";
    Filenames["v4_2_chkaons"] = "v4_2_chkaons";
    Filenames["v4_2_chpions"] = "v4_2_chpions";
    Filenames["v4_2_charged"] = "v4_2_charged";
    Filenames["v5_2_chprotons"] = "v5_2_chprotons";
    Filenames["v5_2_chkaons"] = "v5_2_chkaons";
    Filenames["v5_2_chpions"] = "v5_2_chpions";
    Filenames["v5_2_charged"] = "v5_2_charged";
    Filenames["v2_3_chprotons"] = "v2_3_chprotons";
    Filenames["v2_3_chkaons"] = "v2_3_chkaons";
    Filenames["v2_3_chpions"] = "v2_3_chpions";
    Filenames["v2_3_charged"] = "v2_3_charged";
    Filenames["v3_3_chprotons"] = "v3_3_chprotons";
    Filenames["v3_3_chkaons"] = "v3_3_chkaons";
    Filenames["v3_3_chpions"] = "v3_3_chpions";
    Filenames["v3_3_charged"] = "v3_3_charged";
    Filenames["v4_3_chprotons"] = "v4_3_chprotons";
    Filenames["v4_3_chkaons"] = "v4_3_chkaons";
    Filenames["v4_3_chpions"] = "v4_3_chpions";
    Filenames["v4_3_charged"] = "v4_3_charged";
    Filenames["v5_3_chprotons"] = "v5_3_chprotons";
    Filenames["v5_3_chkaons"] = "v5_3_chkaons";
    Filenames["v5_3_chpions"] = "v5_3_chpions";
    Filenames["v5_3_charged"] = "v5_3_charged";
};

void DataContainer::AddParticle(Statistics::Block &block, Statistics::Line &line) {
    if (line.GetParticlePythiaID() == 211 | line.GetParticlePythiaID() == -211) {
        Histograms3D["pt_chpions"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["yield_chpions"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["meanpt_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());
        Histograms3D["rap_chpions"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["psrap_chpions"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);
        Histograms3D["v2_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        Histograms3D["v2_2_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_2_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_2_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_2_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        Histograms3D["v2_3_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_3_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_3_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_3_chpions"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        Histograms3D["pt_ratio_chpions_to_chkaons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["pt_ratio_chpions_to_chprotons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
    } else if (line.GetParticlePythiaID() == 321 | line.GetParticlePythiaID() == -321) {
        Histograms3D["pt_chkaons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["yield_chkaons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["meanpt_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());
        Histograms3D["rap_chkaons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["psrap_chkaons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);
        Histograms3D["v2_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        Histograms3D["v2_2_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_2_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_2_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_2_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        Histograms3D["v2_3_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_3_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_3_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_3_chkaons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
    } else if (line.GetParticlePythiaID() == 2212 | line.GetParticlePythiaID() == -2212) {
        Histograms3D["pt_chprotons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["yield_chprotons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["meanpt_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());
        Histograms3D["rap_chprotons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["psrap_chprotons"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);
        Histograms3D["v2_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        Histograms3D["v2_2_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_2_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_2_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_2_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        Histograms3D["v2_3_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_3_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_3_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_3_chprotons"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
    }
    if (ChargeMap[line.GetParticlePythiaID()] != 0) {
        Histograms3D["pt_charged"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["yield_charged"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["meanpt_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetTransverseMomentum());
        Histograms3D["rap_charged"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), 1.0);
        Histograms3D["psrap_charged"]->AddCurrent(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetPseudoRapidity(), 1.0);
        Histograms3D["v2_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        Histograms3D["v2_2_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_2_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_2_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_2_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
        Histograms3D["v2_3_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(2));
        Histograms3D["v3_3_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(3));
        Histograms3D["v4_3_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(4));
        Histograms3D["v5_3_charged"]->Add(block.GetImpactParameter(), line.GetTransverseMomentum(), line.GetRapidity(), line.GetAnisotropicFlow(5));
    }
};

void DataContainer::AddEvent(Statistics::Block &block) {
    Histograms1D["impactparameter"]->Add(block.GetImpactParameter(), block.GetImpactParameter());
    Histograms1D["participation"]->Add(block.GetImpactParameter(), block.GetNumberOfParticipantNucleons());
    Histograms3D["pt_chpions"]->AddEvent();
    Histograms3D["pt_ratio_chpions_to_chkaons"]->AddEvent();
    Histograms3D["pt_ratio_chpions_to_chprotons"]->AddEvent();
    Histograms3D["pt_chkaons"]->AddEvent();
    Histograms3D["pt_chprotons"]->AddEvent();
    Histograms3D["pt_charged"]->AddEvent();
    Histograms3D["yield_chpions"]->AddEvent();
    Histograms3D["yield_chkaons"]->AddEvent();
    Histograms3D["yield_chprotons"]->AddEvent();
    Histograms3D["yield_charged"]->AddEvent();
    Histograms3D["rap_chpions"]->AddEvent();
    Histograms3D["rap_chkaons"]->AddEvent();
    Histograms3D["rap_chprotons"]->AddEvent();
    Histograms3D["rap_charged"]->AddEvent();
    Histograms3D["psrap_chpions"]->AddEvent();
    Histograms3D["psrap_chkaons"]->AddEvent();
    Histograms3D["psrap_chprotons"]->AddEvent();
    Histograms3D["psrap_charged"]->AddEvent();
};

void DataContainer::AddEventBlock(std::shared_ptr<Statistics::Block> block) {
    EventBlocks.push_back(std::move(block));
    NumberOfBlocks++;
}

};  // namespace Statistics
