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


    void saveTiff();
    void saveInLocal(std::string sourcePath);
    void saveCalques(std::vector<calque> calques, bool dataReady, calque res);
    void saveJsonFile(std::vector<calque> calques, const std::vector<Resultat> &resultats, int row, int col, int whiteValue);
    bool save(std::vector<calque> _calques, bool dataReady, const std::vector<Resultat> & resultats, int row, int col, calque res, int whiteValue);
    void saveCurrentDisplay(std::string savePath, std::string currentDisplayPath);
    void save_as(std::string path, std::string fileName, std::vector<calque> _calques, bool dataReady, std::vector<Resultat> resultats, int row, int col, calque res, int whiteValue);
    std::string getFileName(std::string filePath, bool withExtension, char seperator);
    void changeSavePaths(std::string newSavePath);


private:
    std::string savePath;
    std::string saveCalquesPath;
    std::string filename;
    std::string localTiffSave;
};

