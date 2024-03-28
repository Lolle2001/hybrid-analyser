#include "Utilities.hpp"
namespace Utilities {

// void Concatenate(std::vector<Statistics::Block> &v1, const std::vector<Statistics::Block> &v2) {
//     v1.insert(std::end(v1), std::begin(v2), std::end(v2));
// };

double igcd(double a, double b, double base) {
    if (a < b) {
        return igcd(b, a, base);
    }
    if (std::fabs(b) < base) {
        return a;
    } else {
        return (igcd(b, a - std::floor(a / b) * b, base));
    }
}

long double GetFileSize(std::filesystem::path filepath, const int option) {
    long double GB = 1000000000.;  // 3
    long double MB = 1000000.;     // 2
    long double KB = 1000;         // 1
    try {
        std::uintmax_t size = std::filesystem::file_size(filepath);
        long double filesize = static_cast<long double>(size);
        switch (option) {
            case 3:
                return filesize / GB;
            case 2:
                return filesize / MB;
            case 1:
                return filesize / KB;
            default:
                return filesize;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error accessing the file: " << e.what() << std::endl;
        return 0.;
    }
}

std::string repeat(int n, std::string c) {
    std::ostringstream os;
    for (int i = 0; i < n; i++)
        os << c;
    return os.str();
}

int GetNBatch(std::string FileDirectory) {
    std::filesystem::path path(FileDirectory);

    std::string directoryname = path.filename();
    std::string datafolder = path.parent_path();

    int nbatch = 0;
    for (const auto &entry : std::filesystem::directory_iterator(FileDirectory)) {
        std::string filename = entry.path().filename();
        if (filename.substr(0, filename.find("_")) == directoryname) {
            // std::cout << filename << std::endl;

            nbatch++;
        }
    }
    return nbatch;
}

}  // namespace Utilities
