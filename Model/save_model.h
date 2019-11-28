#pragma once
#include "boost/filesystem.hpp"
#include <iostream>
#include <regex>
#include <fstream>
#include <vector>

#include <string>

const char separator =
#ifdef _WIN32
                            '\\';
#else
                            '/';
#endif

class calque;

class save_model
{
public:
    save_model();


    void saveTiff();
    void saveCalques();
    void saveJsonFile();
    bool save(std::vector<calque> _calques);
    void save_as(std::string path, std::string fileName, std::vector<calque> _calques);
    std::string getFileName(std::string filePath, bool withExtension, char seperator);


private:
    std::vector<calque> calques;
    std::string savePath;
    std::string saveCalquesPath;
    std::string filename;
};

