#pragma once
#include "../definition.h"
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


    void saveTiff(std::string pathSource);
    void saveCalques();
    void saveJsonFile();
    bool save(std::vector<calque> _calques);
    void save_as(std::string path, std::string fileName, std::vector<calque> _calques);
    std::string getFileName(std::string filePath, bool withExtension, char seperator);
    void changeSavePaths(std::string newSavePath);


private:
    std::vector<calque> calques;
    std::string savePath;
    std::string saveCalquesPath;
    std::string filename;
};

