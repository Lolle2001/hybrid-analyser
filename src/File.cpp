
#include "File.hpp"

namespace Model {

// File::File() {}

void File_iss::SetInitialState(Statistics::Block_iss& block) {
    InitialState = Statistics::Block_iss(block);
}

void File::InitializeDataContainer() {
    FileData.InitialiseHistograms();
};

void File::operator+=(File const& obj) {
    FileData += obj.FileData;
}

void File::WriteData(std::string DataDirectory) {
    FileData.WriteData(DataDirectory);
    // std::cout << "ihello" << std::endl;
    FileData.WriteEventData(DataDirectory);
    // std::cout << "ihello" << std::endl;
}

void File_iss::Parse() {
    FILE* File = fopen(GetFileDirectory().c_str(), "rb");
    if (File) {
        Statistics::Block_iss TempBlock(InitialState);
        Statistics::Line_iss TempLine;
        int total_particles;
        int pid;
        int eventid = 0;
        float array[9];
        while (fread(&total_particles, sizeof(int), 1, File)) {
            eventid++;
            TempBlock.SetNumberOfParticles(total_particles);
            TempBlock.SetEventID(eventid);
            for (int i = 0; i < total_particles; ++i) {
                fread(&pid, sizeof(int), 1, File);
                fread(array, sizeof(float), 9, File);
                TempLine = Statistics::Line_iss(pid, array);
                TempLine.CalculateTransverseMomentum();
                TempLine.CalculateMomentum();
                // TempLine.CalculatePhi(TempBlock.ReactionPlaneAngle);
                TempLine.CalculatePhi();
                TempLine.CalculateAnisotropicFlow(1);
                TempLine.CalculateAnisotropicFlow(2);
                TempLine.CalculateAnisotropicFlow(3);
                TempLine.CalculateAnisotropicFlow(4);
                TempLine.CalculateAnisotropicFlow(5);

                TempLine.CalculatePseudoRapidity();
                TempLine.CalculateRapidity();
                GetFileData().AddParticle(TempBlock, TempLine);
            }
            GetFileData().AddEvent(TempBlock);
            std::shared_ptr<Statistics::Block_iss> block = std::make_shared<Statistics::Block_iss>(TempBlock);
            GetFileData().AddEventBlock(std::move(block));
        }
        GetFileData().ShrinkEventBlocks();

    } else {
#pragma omp critical
        {
            printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
            printf("%-17s : %s\n", "Cannot open file",
                   GetFileDirectory().c_str());
            fflush(stdout);
        }
    }
    fclose(File);
}

void File_ampt::ParseLog() {
    std::ifstream File;
    File.open(LogDirectory.c_str(), std::ios::in);
    if (File.is_open()) {
        std::string line;
        std::string dummy1, dummy2, dummy3, dummy4, dummy5;
        Statistics::Log_ampt templog;
        int eventid;
        int eventiter;
        double impactpar;
        int nit;
        int ncoll;
        int nitprev;
        int counter = -1;
        while (std::getline(File, line)) {
            if (line.find("#impact parameter,nlop,ncolt=") != std::string::npos) {
                std::istringstream iss(line);
                iss >> dummy1 >> dummy2 >> impactpar >> nit >> ncoll;

                EventInfo[counter]->eventiteration.push_back(nit);
                EventInfo[counter]->impactparameter.push_back(impactpar);
                EventInfo[counter]->ncoll.push_back(ncoll);
                // std::cout << *EventInfo[counter] << std::endl;

            } else if (line.find("EVENT") != std::string::npos) {
                std::istringstream iss(line);

                iss >> dummy1 >> eventid >> dummy2 >> eventiter;
                templog.eventid = eventid;
                std::shared_ptr<Statistics::Log_ampt> block = std::make_shared<Statistics::Log_ampt>(templog);
                EventInfo.push_back(std::move(block));
                counter++;
            }
        }

    } else {
#pragma omp critical
        {
            printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
            printf("%-17s : %s\n", "Cannot open file",
                   GetFileDirectory().c_str());
            fflush(stdout);
        }
    }
    File.close();
}

void File_ampt::Parse() {
    // #pragma omp critical
    //     {
    //         printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    //         printf("%-17s : %s\n", "Parsing data from", GetFileDirectory().c_str());
    //         fflush(stdout);
    //     }
    ParseLog();

    std::ifstream File;
    File.open(GetFileDirectory().c_str(), std::ios::in);
    if (File.is_open()) {
        Statistics::Block_ampt TempBlock;
        Statistics::Line_ampt TempLine;
        int counter = 0;
        while (File >> TempBlock) {
            TempBlock.SetNumberOfBinaryCollisions(EventInfo[counter]->ncoll.back());

            for (int i = 0; i < TempBlock.GetNumberOfParticles(); ++i) {
                File >> TempLine;

                TempLine.CalculateProperties(1, 5);
                // TempLine.CalculateAnisotropicFlowCos(2);
                // TempLine.CalculateAnisotropicFlowSin(2);
                GetFileData().AddParticle(TempBlock, TempLine);
            }

            GetFileData().AddEvent(TempBlock);
            std::shared_ptr<Statistics::Block_ampt> block = std::make_shared<Statistics::Block_ampt>(TempBlock);
            GetFileData().AddEventBlock(std::move(block));
            counter++;
        }
        GetFileData().ShrinkEventBlocks();

        // #pragma omp critical
        //         {
        //             printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
        //             printf("%-17s : %s\n", "Parsed data from",
        //                    GetFileDirectory().c_str());
        //             fflush(stdout);
        //         }

    } else {
#pragma omp critical
        {
            printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
            printf("%-17s : %s\n", "Cannot open file",
                   GetFileDirectory().c_str());
            fflush(stdout);
        }
    }
    File.close();
}

void File_ampt::ParseFull() {
    ParseLog();

    std::ifstream File;
    File.open(GetFileDirectory().c_str(), std::ios::in);
    if (File.is_open()) {
        Statistics::Block_ampt TempBlock;
        Statistics::Line_ampt TempLine;

        int counter = 0;
        while (File >> TempBlock) {
            TempBlock.SetNumberOfBinaryCollisions(EventInfo[counter]->ncoll.back());

            std::vector<Statistics::Line_ampt> TempLineVector;
            double vncos[Statistics::NUMBER_OF_HARMONICS + 1] = {0};
            double vnsin[Statistics::NUMBER_OF_HARMONICS + 1] = {0};
            unsigned long int chparticlemp = 0;

            for (int i = 0; i < TempBlock.GetNumberOfParticles(); ++i) {
                File >> TempLine;

                // std::cout << TempLine << std::endl;

                TempLine.CalculateProperties(1, Statistics::NUMBER_OF_HARMONICS);
                for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                    TempLine.CalculateAnisotropicFlowCos(n);
                    TempLine.CalculateAnisotropicFlowSin(n);
                    vncos[n] += TempLine.GetAnisotropicFlowCos(n) * TempLine.GetTransverseMomentum();
                    vnsin[n] += TempLine.GetAnisotropicFlowSin(n) * TempLine.GetTransverseMomentum();
                }

                if (Statistics::ChargeMap[TempLine.GetParticlePythiaID()] != 0) {
                    if (TempLine.GetPseudoRapidity() >= -0.5 && TempLine.GetPseudoRapidity() <= 0.5) {
                        chparticlemp++;
                    }
                }

                TempLineVector.push_back(TempLine);
            }
            // std::cout << "vnsin = " << vnsin[2] << std::endl;
            // std::cout << "vncos = " << vncos[2] << std::endl;
            TempBlock.SetNumberOfChargedParticles(chparticlemp);
            for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                // TempBlock.CalculateEventPlaneAngle(n, vnsin[n], vncos[n]);
                TempBlock.SetEventPlaneAngle(n, 1. / n * std::atan2(vnsin[n], vncos[n]));
            }
            // std::cout << "Psi_EP = " << TempBlock.GetEventPlaneAngle(2) << std::endl;

            for (int i = 0; i < TempBlock.GetNumberOfParticles(); ++i) {
                for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                    TempLineVector[i].CalculatePhi(TempBlock.GetEventPlaneAngle(n));
                    TempLineVector[i].CalculateAnisotropicFlow(n);
                }
                // std::cout << TempLineVector[i] << std::endl;
                GetFileData().AddParticle(TempBlock, TempLineVector[i]);
            }

            GetFileData().AddEvent(TempBlock);
            std::shared_ptr<Statistics::Block_ampt> block = std::make_shared<Statistics::Block_ampt>(TempBlock);
            GetFileData().AddEventBlock(std::move(block));
            counter++;
        }
        GetFileData().ShrinkEventBlocks();

    } else {
#pragma omp critical
        {
            printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
            printf("%-17s : %s\n", "Cannot open file",
                   GetFileDirectory().c_str());
            fflush(stdout);
        }
    }
    File.close();
}

void File_iss::ParseFull() {
    FILE* File = fopen(GetFileDirectory().c_str(), "rb");
    if (File) {
        Statistics::Block_iss TempBlock(InitialState);
        Statistics::Line_iss TempLine;
        int total_particles;
        int pid;
        int eventid = 0;
        float array[9];
        while (fread(&total_particles, sizeof(int), 1, File)) {
            eventid++;
            TempBlock.SetNumberOfParticles(total_particles);
            TempBlock.SetEventID(eventid);
            std::vector<Statistics::Line_iss> TempLineVector(total_particles);
            double vncos[Statistics::NUMBER_OF_HARMONICS + 1] = {0};
            double vnsin[Statistics::NUMBER_OF_HARMONICS + 1] = {0};
            for (int i = 0; i < total_particles; ++i) {
                fread(&pid, sizeof(int), 1, File);
                fread(array, sizeof(float), 9, File);
                TempLine = Statistics::Line_iss(pid, array);

                TempLine.CalculateTransverseMomentum();
                TempLine.CalculateMomentum();
                TempLine.CalculatePhi();
                for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                    TempLine.CalculateAnisotropicFlow(n);
                    TempLine.CalculateAnisotropicFlowCos(n);
                    TempLine.CalculateAnisotropicFlowSin(n);
                    vncos[n] += TempLine.GetAnisotropicFlowCos(n) * TempLine.GetTransverseMomentum();
                    vnsin[n] += TempLine.GetAnisotropicFlowSin(n) * TempLine.GetTransverseMomentum();
                }

                TempLine.CalculatePseudoRapidity();
                TempLine.CalculateRapidity();
                // std::cout << TempLine << std::endl;
                TempLineVector[i] = TempLine;
            }

            for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                // TempBlock.CalculateEventPlaneAngle(n, vnsin[n], vncos[n]);
                TempBlock.SetEventPlaneAngle(n, 1. / n * std::atan2(vnsin[n], vncos[n]));
            }
            for (int i = 0; i < total_particles; ++i) {
                for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                    TempLineVector[i].CalculatePhi(TempBlock.GetEventPlaneAngle(n));
                    TempLineVector[i].CalculateAnisotropicFlow(n);
                }
                GetFileData().AddParticle(TempBlock, TempLineVector[i]);
            }
            GetFileData().AddEvent(TempBlock);
            std::shared_ptr<Statistics::Block_iss> block = std::make_shared<Statistics::Block_iss>(TempBlock);
            GetFileData().AddEventBlock(std::move(block));
        }
        GetFileData().ShrinkEventBlocks();

    } else {
#pragma omp critical
        {
            printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
            printf("%-17s : %s\n", "Cannot open file",
                   GetFileDirectory().c_str());
            fflush(stdout);
        }
    }
    fclose(File);
}

void File_ampt::ParseEventStatistics() {
    ParseLog();
    std::ifstream File;
    File.open(GetFileDirectory().c_str(), std::ios::in);
    if (File.is_open()) {
        Statistics::Block_ampt TempBlock;
        Statistics::Line_ampt TempLine;

        int counter = 0;
        while (File >> TempBlock) {
            TempBlock.SetNumberOfBinaryCollisions(EventInfo[counter]->ncoll.back());

            std::vector<Statistics::Line_ampt> TempLineVector;
            double vncos[Statistics::NUMBER_OF_HARMONICS + 1] = {0};
            double vnsin[Statistics::NUMBER_OF_HARMONICS + 1] = {0};
            unsigned long int chparticlemp = 0;

            for (int i = 0; i < TempBlock.GetNumberOfParticles(); ++i) {
                File >> TempLine;

                // std::cout << TempLine << std::endl;

                TempLine.CalculateProperties(1, Statistics::NUMBER_OF_HARMONICS);
                for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                    TempLine.CalculateAnisotropicFlowCos(n);
                    TempLine.CalculateAnisotropicFlowSin(n);
                    vncos[n] += TempLine.GetAnisotropicFlowCos(n) * TempLine.GetTransverseMomentum();
                    vnsin[n] += TempLine.GetAnisotropicFlowSin(n) * TempLine.GetTransverseMomentum();
                }

                if (Statistics::ChargeMap[TempLine.GetParticlePythiaID()] != 0) {
                    if (TempLine.GetPseudoRapidity() >= -0.5 && TempLine.GetPseudoRapidity() <= 0.5) {
                        chparticlemp++;
                    }
                }

                TempLineVector.push_back(TempLine);
            }
            // std::cout << "vnsin = " << vnsin[2] << std::endl;
            // std::cout << "vncos = " << vncos[2] << std::endl;
            TempBlock.SetNumberOfChargedParticles(chparticlemp);
            for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                // TempBlock.CalculateEventPlaneAngle(n, vnsin[n], vncos[n]);
                TempBlock.SetEventPlaneAngle(n, 1. / n * std::atan2(vnsin[n], vncos[n]));
            }
            // std::cout << "Psi_EP = " << TempBlock.GetEventPlaneAngle(2) << std::endl;

            std::shared_ptr<Statistics::Block_ampt> block = std::make_shared<Statistics::Block_ampt>(TempBlock);
            GetFileData().AddEventBlock(std::move(block));
            counter++;
        }
        GetFileData().ShrinkEventBlocks();
        // GetFileData().CalculateCentralityClasses();

    } else {
#pragma omp critical
        {
            printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
            printf("%-17s : %s\n", "Cannot open file",
                   GetFileDirectory().c_str());
            fflush(stdout);
        }
    }
    File.close();
}

void File_ampt::ParseParticleStatistics() {
    std::ifstream File;
    File.open(GetFileDirectory().c_str(), std::ios::in);
    if (File.is_open()) {
        Statistics::Block TempBlock;
        Statistics::Block_ampt TempBlock_ampt;
        Statistics::Line_ampt TempLine;

        int counter = 0;
        while (File >> TempBlock_ampt) {
            TempBlock = *(GetFileData().GetEventBlock(counter));
            for (int i = 0; i < TempBlock.GetNumberOfParticles(); ++i) {
                File >> TempLine;
                // std::cout << TempLine << std::endl;
                TempLine.CalculateProperties(1, Statistics::NUMBER_OF_HARMONICS);

                for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                    TempLine.CalculatePhi(GetFileData().GetEventBlock(counter)->GetEventPlaneAngle(n));
                    TempLine.CalculateAnisotropicFlow(n);
                    TempLine.CalculateAnisotropicFlowOld(n);
                }

                GetFileData().AddParticle(TempBlock, TempLine);
            }
            GetFileData().AddEvent(TempBlock);
            // std::cout << TempBlock.GetNumberOfChargedParticles() << std::endl;
            counter++;
        }

    } else {
#pragma omp critical
        {
            printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
            printf("%-17s : %s\n", "Cannot open file",
                   GetFileDirectory().c_str());
            fflush(stdout);
        }
    }
    File.close();
}

void File_iss::ParseEventStatistics() {
    FILE* File = fopen(GetFileDirectory().c_str(), "rb");

    if (File) {
        Statistics::Block_iss TempBlock(InitialState);
        Statistics::Line_iss TempLine;
        int total_particles;
        int pid;
        int eventid = 0;
        float array[9];
        while (fread(&total_particles, sizeof(int), 1, File)) {
            eventid++;
            TempBlock.SetNumberOfParticles(total_particles);
            TempBlock.SetEventID(eventid);
            // std::vector<Statistics::Line_iss> TempLineVector(total_particles);
            double vncos[Statistics::NUMBER_OF_HARMONICS + 1] = {0};
            double vnsin[Statistics::NUMBER_OF_HARMONICS + 1] = {0};
            unsigned int long chparticlemp = 0;
            for (int i = 0; i < TempBlock.GetNumberOfParticles(); ++i) {
                fread(&pid, sizeof(int), 1, File);
                fread(array, sizeof(float), 9, File);
                TempLine = Statistics::Line_iss(pid, array);

                TempLine.CalculateTransverseMomentum();
                TempLine.CalculateMomentum();
                TempLine.CalculatePhi();
                for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                    TempLine.CalculateAnisotropicFlow(n);
                    TempLine.CalculateAnisotropicFlowCos(n);
                    TempLine.CalculateAnisotropicFlowSin(n);
                    vncos[n] += TempLine.GetAnisotropicFlowCos(n) * TempLine.GetTransverseMomentum();
                    vnsin[n] += TempLine.GetAnisotropicFlowSin(n) * TempLine.GetTransverseMomentum();
                }

                if (Statistics::ChargeMap[TempLine.GetParticlePythiaID()] != 0) {
                    if (TempLine.GetPseudoRapidity() >= -0.5 && TempLine.GetPseudoRapidity() <= 0.5) {
                        chparticlemp++;
                    }
                }

                // TempLineVector.push_back(TempLine);
            }
            // std::cout << "vnsin = " << vnsin[2] << std::endl;
            // std::cout << "vncos = " << vncos[2] << std::endl;
            TempBlock.SetNumberOfChargedParticles(chparticlemp);
            for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                // TempBlock.CalculateEventPlaneAngle(n, vnsin[n], vncos[n]);
                TempBlock.SetEventPlaneAngle(n, 1. / n * std::atan2(vnsin[n], vncos[n]));
            }
            // std::cout << "Psi_EP = " << TempBlock.GetEventPlaneAngle(2) << std::endl;

            std::shared_ptr<Statistics::Block_iss> block = std::make_shared<Statistics::Block_iss>(TempBlock);
            GetFileData().AddEventBlock(std::move(block));
        }
        GetFileData().ShrinkEventBlocks();
        // GetFileData().CalculateCentralityClasses();

    } else {
#pragma omp critical
        {
            printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
            printf("%-17s : %s\n", "Cannot open file",
                   GetFileDirectory().c_str());
            fflush(stdout);
        }
    }
    fclose(File);
}

void File_iss::ParseParticleStatistics() {
    FILE* File = fopen(GetFileDirectory().c_str(), "rb");
    if (File) {
        Statistics::Block TempBlock;
        Statistics::Block_iss TempBlock_iss(InitialState);
        Statistics::Line_iss TempLine;
        int total_particles;
        int pid;

        float array[9];
        int counter = 0;
        while (fread(&total_particles, sizeof(int), 1, File)) {
            TempBlock = *(GetFileData().GetEventBlock(counter));
            for (int i = 0; i < total_particles; ++i) {
                fread(&pid, sizeof(int), 1, File);
                fread(array, sizeof(float), 9, File);
                TempLine = Statistics::Line_iss(pid, array);

                TempLine.CalculateTransverseMomentum();
                TempLine.CalculateMomentum();
                TempLine.CalculatePhi();
                for (int n = 1; n <= Statistics::NUMBER_OF_HARMONICS; n++) {
                    TempLine.CalculatePhi(GetFileData().GetEventBlock(counter)->GetEventPlaneAngle(n));
                    TempLine.CalculateAnisotropicFlow(n);
                    TempLine.CalculateAnisotropicFlowOld(n);
                }

                TempLine.CalculatePseudoRapidity();
                TempLine.CalculateRapidity();
                // std::cout << TempLine << std::endl;
                GetFileData().AddParticle(TempBlock, TempLine);
            }

            GetFileData().AddEvent(TempBlock);
            counter++;
        }

    } else {
#pragma omp critical
        {
            printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
            printf("%-17s : %s\n", "Cannot open file",
                   GetFileDirectory().c_str());
            fflush(stdout);
        }
    }
    fclose(File);
}

}  // namespace Model
