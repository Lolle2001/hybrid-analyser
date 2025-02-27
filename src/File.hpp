// Copyright (C) 2024 Lieuwe Huisman
#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>

#include "DataContainer.hpp"
#include "DataFormat.hpp"
#include "ParticleProperties.hpp"

namespace Model {

class File {
   private:
    std::string FileDirectory;
    Statistics::DataContainer FileData;

   public:
    File(){};

    File(int collisiontype) {
        FileData = Statistics::DataContainer();
        FileData.SetCentralityType(collisiontype);
    }

    File(std::string FileDirectory_, int collisiontype) : FileDirectory(FileDirectory_) {
        FileData = Statistics::DataContainer();
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

    File_iss(int collisiontype) : File(collisiontype){};

    File_iss(std::string FileDirectory_, int collisiontype) : File(FileDirectory_, collisiontype){};

    void Parse();

    void ParseFull();

    void ParseEventStatistics();
    void ParseParticleStatistics();

    void SetInitialState(Statistics::Block_iss& block);
};

class File_ampt : public File {
   private:
    std::vector<std::shared_ptr<Statistics::Log_ampt>> EventInfo;

    std::string LogDirectory;

   public:
    File_ampt() : File(){};

    File_ampt(int collisiontype) : File(collisiontype){};

    File_ampt(std::string FileDirectory_, int collisiontype) : File(FileDirectory_, collisiontype){};

    File_ampt(std::string LogDirectory_, std::string FileDirectory_, int collisiontype) : LogDirectory(LogDirectory_), File(FileDirectory_, collisiontype){};

    void Parse();
    void ParseEventStatistics();
    void ParseParticleStatistics();
    void ParseLogStatistics();
    void ParseLog();

    void ParseFull();

    // void StackBlocks(std::vector<std::unique_ptr<File_ampt>> files) {

    // int StartIndex = NumberOfBlocks - obj.NumberOfBlocks;
    // // std::cout << EventBlocks.size() << std::endl;
    // // std::cout << StartIndex << std::endl;

    // for (int i = StartIndex; i < NumberOfBlocks; ++i) {
    //     EventBlocks[i]->SetEventID(EventBlocks[i]->GetEventID() + StartIndex);
    // }
    // };
};

};  // namespace Model

#endif