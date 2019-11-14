#pragma once
//#include <boost/filesystem>
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

    void saveCalques();
    void saveJsonFile();
    void save();
    void save_as(std::string path, std::string filename,std::vector<calque> _calques);

    bool getCanSave() const;

private:
    std::vector<calque> calques;
    std::string savePath;
    std::string saveCalquesPath;
    bool canSave;
};

