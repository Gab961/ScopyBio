#pragma once
#include "../definition.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <vector>
#include <string>

class calque;
class Resultat;
class Qpoint;

class save_model
{
public:
    save_model();


    void saveTiff(std::string pathSource);
    void saveCalques(std::vector<calque> calques);
    void saveJsonFile(std::vector<calque> calques, const std::vector<Resultat> &resultats);
    bool save(std::vector<calque> _calques,const std::vector<Resultat> & resultats);
    void save_as(std::string path, std::string fileName, std::vector<calque> _calques, std::vector<Resultat> resultats);
    std::string getFileName(std::string filePath, bool withExtension, char seperator);
    void changeSavePaths(std::string newSavePath);


private:
    std::string savePath;
    std::string saveCalquesPath;
    std::string filename;
};

