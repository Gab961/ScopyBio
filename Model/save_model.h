#pragma once
#include <vector>

#include <string>

class calque;

class save_model
{
public:
    save_model(std::string path, std::string filename,std::vector<calque> _calques);


    inline char separator();

    void saveCalques();
    void saveJsonFile();
    void save();

private:
    std::vector<calque> calques;
    std::string savePath;
    std::string saveCalquesPath;
};

