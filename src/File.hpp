#ifndef FILE_HPP
#define FILE_HPP

#include <string>

#include "DataContainer.hpp"
#include "DataFormat.hpp"

namespace Model {

class File {
   private:
    std::string FileDirectory;
    Statistics::DataContainer FileData;

   public:
    File(){};

    File(std::string FileDirectory_, int collisiontype) : FileDirectory(FileDirectory_) {
        FileData.SetCentralityType(collisiontype);
    };

    void InitializeDataContainer();

    std::string GetFileDirectory() const { return FileDirectory; };

    Statistics::DataContainer& GetFileData() { return FileData; };

    void WriteData(std::string DataDirectory);

    void operator+=(File const& obj);
};

class File_iss : public File {
   private:
    Statistics::Block_iss InitialState;

   public:
    File_iss() : File(){};

    File_iss(std::string FileDirectory_, int collisiontype) : File(FileDirectory_, collisiontype){};

    void Parse();

    void SetInitialState(Statistics::Block_iss& block);
};

class File_ampt : public File {
   private:
   public:
    void Parse();

    File_ampt() : File(){};

    File_ampt(std::string FileDirectory_, int collisiontype) : File(FileDirectory_, collisiontype){};
};

};  // namespace Model

#endif