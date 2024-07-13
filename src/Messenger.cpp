// Copyright (C) 2024 Lieuwe Huisman
#include "Messenger.hpp"

namespace Utilities {

void PretyPrint::Warning(const std::string& text) {
    printf("%s%s%s\n", PretyPrint::WARNING, text.c_str(), PretyPrint::RESET);
}
void PretyPrint::Started(const std::string& text) {
    printf("%s%s%s\n", PretyPrint::STARTED, text.c_str(), PretyPrint::RESET);
}
void PretyPrint::Finished(const std::string& text) {
    printf("%s%s%s\n", PretyPrint::FINISHED, text.c_str(), PretyPrint::RESET);
}
void PretyPrint::Highlight(const std::string& text) {
    printf("%s%s%s\n", PretyPrint::HIGHLIGHT, text.c_str(), PretyPrint::RESET);
}

// void PretyPrint::PrintFileSize(const std::string &filename, const int sizeindex) {
//     double Filesize = Utilities::GetFileSize(filename, 1);
//     printf("%s%s%s ", PretyPrint::FINISHED, "[INFO]", PretyPrint::RESET);
//     printf("%s[%07.3fKB]%s ", PretyPrint::HIGHLIGHT, Filesize, PretyPrint::RESET);
//     printf("%-14s : %s\n", "Writen data to", filename.c_str());
//     fflush(stdout);
// }

}  // namespace Utilities

namespace cst {
namespace man {
std::ostream& warning(std::ostream& os) {
    os << fmt::format("{}[WARNING]{} ", color::WARNING, color::RESET);
    return os;
};
std::ostream& error(std::ostream& os) {
    os << fmt::format("{}[ERROR]{} ", color::ERROR, color::RESET);
    return os;
};
std::ostream& done(std::ostream& os) {
    os << fmt::format("{}[INFO]{} ", color::FINISHED, color::RESET);
    return os;
};
std::ostream& pending(std::ostream& os) {
    os << fmt::format("{}[INFO]{} ", color::STARTED, color::RESET);
    return os;
};
std::ostream& highlight(std::ostream& os) {
    os << fmt::format("{}[INFO]{} ", color::HIGHLIGHT, color::RESET);
    return os;
}
std::ostream& debug(std::ostream& os) {
    os << fmt::format("{}[DEBUG]{} ", color::DEBUG, color::RESET);
    return os;
};
std::ostream& success(std::ostream& os) {
    os << fmt::format("{}[SUCCESS]{} ", color::SUCCESS, color::RESET);
    return os;
};
std::ostream& deprecation_warning(std::ostream& os) {
    os << fmt::format("{}[DEPRECATION WARNING]{} ", color::DEPRECATION, color::RESET);
    return os;
};
std::ostream& critical(std::ostream& os) {
    os << fmt::format("{}[CRITICAL]{} ", color::CRITICAL, color::RESET);
    return os;
};
std::ostream& trace(std::ostream& os) {
    os << fmt::format("{}[TRACE]{} ", color::TRACE, color::RESET);
    return os;
};
std::ostream& prompt(std::ostream& os) {
    os << fmt::format("{}[PROMPT]{} ", color::PROMPT, color::RESET);
    return os;
};

// std::ostream & byteconversion(std::ostream & os, const std::string& unit ){
//     double conversion = 1.0;
//     if(unit == "GB"){
//         conversion = 1000000000.0;
//     } else if(unit == "MB"){
//         conversion = 1000000.0;
//     } else if(unit == "KB"){
//         conversion = 1000.0;
//     } else if(unit == "B"){
//         conversion = 1.0;
//     } else {
//         os << warning << "Unknown unit: " << unit << std::endl;
//         return os;
//     }
//     os << conversion;
//     return os;
// }
// std::ostream & operator<< (std::ostream & os, const std::pair<std::string, double> & data){
//     double sizeinunit = data.second/std::stod(data.first);
//     os << sizeinunit;
//     return os;
// }

}  // namespace man
}  // namespace cst