#pragma once
#include "boost/filesystem.hpp"
#include <iostream>
#include <regex>
#include <fstream>
#include <vector>

#include <string>

class calque;

class save_model
{
public:
    save_model();


    inline char separator();

    void saveTiff();
    void saveCalques();
    void saveJsonFile();
    void save(std::vector<calque> _calques);
    void save_as(std::string path, std::string fileName, std::vector<calque> _calques);
    std::string getFileName(std::string filePath, bool withExtension, char seperator);

    bool getCanSave() const;

private:
    std::vector<calque> calques;
    std::string savePath;
    std::string saveCalquesPath;
    std::string filename;
    bool canSave;
};

