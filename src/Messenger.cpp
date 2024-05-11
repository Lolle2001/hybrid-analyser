#include "Messenger.hpp"

namespace Utilities {

void PretyPrint::Warning(const std::string &text) {
    printf("%s%s%s\n", PretyPrint::WARNING, text.c_str(), PretyPrint::RESET);
}
void PretyPrint::Started(const std::string &text) {
    printf("%s%s%s\n", PretyPrint::STARTED, text.c_str(), PretyPrint::RESET);
}
void PretyPrint::Finished(const std::string &text) {
    printf("%s%s%s\n", PretyPrint::FINISHED, text.c_str(), PretyPrint::RESET);
}
void PretyPrint::Highlight(const std::string &text) {
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
