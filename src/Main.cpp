#include <iomanip>
#include <iostream>
#include <string>

#include "File.hpp"
#include "FileProcessor.hpp"
#include "Utilities.hpp"

namespace AMPT {
void Main(int argc, char* argv[]) {
    int NRun;
    int NBatch;
    std::string Directory;
    int collisiontype;
    int LowerNBatch = 1;

    // std::cout << "hallo" << std::endl;

    bool flag_nr = false;
    bool flag_nb = false;
    bool flag_dir = false;
    bool flag_col = false;

    for (int i = 1; i < argc - 1; ++i) {
        // std::cout << i << " " << argv[i] << std::endl;
        if (std::string(argv[i]).compare("-nr") == 0) {
            NRun = std::stoi(argv[i + 1]);
            flag_nr = true;
            i++;
        }
        if (std::string(argv[i]).compare("-nb") == 0) {
            NBatch = std::stoi(argv[i + 1]);
            flag_nb = true;
            i++;
        }
        if (std::string(argv[i]).compare("-dir") == 0) {
            Directory = argv[i + 1];
            flag_dir = true;
            i++;
        }
        if (std::string(argv[i]).compare("-col") == 0) {
            collisiontype = std::stoi(argv[i + 1]);
            flag_col = true;
            i++;
        }
        if (std::string(argv[i]).compare("-nbmin") == 0) {
            LowerNBatch = std::stoi(argv[i + 1]);
            // flag_col = true;
            i++;
        }
    }
    // std::cout << "hallo" << std::endl;
    if (!flag_nr) {
        NRun = std::stoi(argv[2]);
    }
    if (!flag_dir) {
        Directory = "/home/lieuwe/Documents/Software/AMPT/data";
    }
    if (!flag_nb) {
        NBatch = Utilities::GetNBatch(Directory + "/" + std::to_string(NRun));
    }
    if (!flag_col) {
        collisiontype = 0;
    }
    std::string centralitybinningname;
    if (collisiontype == 0) {
        centralitybinningname = "Pb-Pb at 5.02 TeV (0-5-10-20-..90-100)";
    }
    if (collisiontype == 1) {
        centralitybinningname = "p-Pb at 5.02 TeV (0-5-10-20-..90-100)";
    }
    if (collisiontype == 2) {
        centralitybinningname = "p-p at 5.02 TeV (0-100)";
    }
    // std::cout << collisiontype << std::endl;
    // std::cout << "hallo" << std::endl;
    // std::cout << "\033[1;48;2;0;111;184";

    printf("%s╭%-70s╮%s\n", PP::HIGHLIGHT, Utilities::repeat(70, "─").c_str(), PP::RESET);
    printf("%s│%s %-68s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "AMPT data processer for large data", PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-68s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Version 3.1.0", PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-68s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Made by Lieuwe Huisman", PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-68s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Made for AMPT version: v23.02.2024", PP::HIGHLIGHT, PP::RESET);
    printf("%s├%-70s┤%s\n", PP::HIGHLIGHT, Utilities::repeat(70, "─").c_str(), PP::RESET);
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Runnumber", std::to_string(NRun).c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Batchnumber", std::to_string(NBatch).c_str(), PP::HIGHLIGHT, PP::RESET);
    if (LowerNBatch > 1) {
        printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Starting at bin", std::to_string(LowerNBatch).c_str(), PP::HIGHLIGHT, PP::RESET);
    }
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Data directory", Directory.c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Centrality Binning", centralitybinningname.c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s╰%-70s╯%s\n", PP::HIGHLIGHT, Utilities::repeat(70, "─").c_str(), PP::RESET);

    AMPT::ReadFiles(NRun, LowerNBatch, NBatch, Directory, collisiontype);

    // AMPT::File_ampt* ampt = Model::CombineAMPT(NRun, LowerNBatch, NBatch, Directory + "/", 20, collisiontype);
    // AMPT::File_input* input = Model::Combine_file_input(NRun, LowerNBatch, NBatch, Directory + "/");
}
};  // namespace AMPT

namespace iSS {
void Main(int argc, char* argv[]) {
    int NRun;
    int IPGlasmaRun;
    std::string Directory;
    std::string ParameterFile;
    int NEvent;
    int collisiontype = 0;

    bool flag_nr = false;
    bool flag_nrip = false;
    bool flag_ne = false;
    bool flag_dir = false;
    bool flag_col = false;
    bool flag_par = false;

    for (int i = 1; i < argc - 1; ++i) {
        // std::cout << i << " " << argv[i] << std::endl;
        if (std::string(argv[i]).compare("-nr") == 0) {
            NRun = std::stoi(argv[i + 1]);
            flag_nr = true;
            i++;
        }
        if (std::string(argv[i]).compare("-nrip") == 0) {
            IPGlasmaRun = std::stoi(argv[i + 1]);
            flag_nrip = true;
            i++;
        }
        if (std::string(argv[i]).compare("-ne") == 0) {
            NEvent = std::stoi(argv[i + 1]);
            flag_ne = true;
            i++;
        }
        if (std::string(argv[i]).compare("-dir") == 0) {
            Directory = argv[i + 1];
            flag_dir = true;
            i++;
        }
        if (std::string(argv[i]).compare("-col") == 0) {
            collisiontype = std::stoi(argv[i + 1]);
            flag_col = true;
            i++;
        }
        if (std::string(argv[i]).compare("-par") == 0) {
            ParameterFile = argv[i + 1];
            // flag_col = true;
            i++;
        }
    }

    if (!flag_nr) {
        NRun = std::stoi(argv[2]);
    }
    if (!flag_nrip) {
        IPGlasmaRun = NRun;
    }
    if (!flag_dir) {
        Directory = "/home/lieuwe/Documents/Software/iSS/data";
    }
    if (!flag_ne) {
        NEvent = Utilities::GetNBatch(Directory + "/" + std::to_string(NRun));
    }
    if (!flag_col) {
        collisiontype = 0;
    }
    if (!flag_par) {
        ParameterFile = "ProcessParameters.par";
    }

    std::string centralitybinningname;
    if (collisiontype == 0) {
        centralitybinningname = "Pb-Pb at 5.02 TeV (0-5-10-20-..90-100)";
    }
    if (collisiontype == 1) {
        centralitybinningname = "p-Pb at 5.02 TeV (0-5-10-20-..90-100)";
    }
    if (collisiontype == 2) {
        centralitybinningname = "p-p at 5.02 TeV (0-100)";
    }

    printf("%s╭%-70s╮%s\n", PP::HIGHLIGHT, Utilities::repeat(70, "─").c_str(), PP::RESET);
    printf("%s│%s %-68s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "iSS data processer for large data", PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-68s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Version 3.1.0", PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-68s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Made by Lieuwe Huisman", PP::HIGHLIGHT, PP::RESET);
    printf("%s├%-70s┤%s\n", PP::HIGHLIGHT, Utilities::repeat(70, "─").c_str(), PP::RESET);
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Runnumber", std::to_string(NRun).c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "IPGlasma runnumber", std::to_string(IPGlasmaRun).c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Number of events", std::to_string(NEvent).c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Data directory", Directory.c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT, PP::RESET, "Centrality Binning", centralitybinningname.c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s╰%-70s╯%s\n", PP::HIGHLIGHT, Utilities::repeat(70, "─").c_str(), PP::RESET);

    iSS::ReadFiles(NRun, IPGlasmaRun, NEvent, ParameterFile, collisiontype);
}
};  // namespace iSS

int main(int argc, char* argv[]) {
    if (argc > 2) {
        if (std::string(argv[1]).compare("hydro") == 0) {
            iSS::Main(argc, argv);
        } else if (std::string(argv[1]).compare("transport") == 0) {
            AMPT::Main(argc, argv);
        } else {
            std::cout << "Please enter a valid model as the first argument!" << std::endl;
        }
    } else {
        std::cout << "Do not forget to specify the runnumber!" << std::endl;
    }
}